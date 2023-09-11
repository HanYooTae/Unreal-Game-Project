#include "ActorComponent/CInventoryComponent.h"
#include "Net/UnrealNetwork.h"
#include "UObject/UObjectBase.h"
#include "Engine/ActorChannel.h"

#define LOCTEXT_NAMESPACE "Inventory"

UCInventoryComponent::UCInventoryComponent()
{	
	// object�� ���� �ϱ����� �Լ� SetIsReplicated�� callstack�� �Ͼ SetIsReplicatedByDefault�� �����
	SetIsReplicatedByDefault(true);
}

FItemAddResult UCInventoryComponent::TryAddItem(UCItem* Item)
{
	return TryAddItem_Internal(Item);
}

FItemAddResult UCInventoryComponent::TryAddItemFromClass(TSubclassOf<class UCItem> ItemClass, const int32 Quantity)
{
	UCItem* Item = NewObject<UCItem>(GetOwner(), ItemClass);
	Item->SetQuantity(Quantity);
	return TryAddItem_Internal(Item);
}

int32 UCInventoryComponent::ConsumeItem(class UCItem* Item)
{
	if (Item)
	{
		ConsumeItem(Item, Item->GetQuantity());
	}

	return 0;
}

int32 UCInventoryComponent::ConsumeItem(class UCItem* Item, const int32 Quantity)
{
	if (GetOwner() && GetOwner()->HasAuthority() && Item)
	{
		const int32 RemoveQuantity = FMath::Min(Quantity, Item->GetQuantity());

		//�������� ����߸� �Ŀ��� ���̳ʽ� �ݾ��� ���;� ��.
		ensure(!(Item->GetQuantity() - RemoveQuantity < 0)); // ǥ������ �����Ͽ� �����ϸ� �� �������� �̸��� �ݽ����� �����մϴ�.

		//���� �� �׸��� �����ϴ�.�κ��丮���� �����ϼ���.
		Item->SetQuantity(Item->GetQuantity() - RemoveQuantity);

		if (Item->GetQuantity() <= 0)
		{
			RemoveItem(Item);
		}
		else
		{
			ClientRefreshInventory();
		}

		return RemoveQuantity;
	}

	return 0;
}

bool UCInventoryComponent::RemoveItem(UCItem* Item)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		if (Item)
		{
			Items.RemoveSingle(Item);

			ReplicatedItemsKey++;

			return true;
		}
	}

	return false;
}

bool UCInventoryComponent::HasItem(TSubclassOf<class UCItem> ItemClass, const int32 Quantity) const
{
	if (UCItem* ItemToFind = FindItemByClass(ItemClass))
	{
		return ItemToFind->GetQuantity() >= Quantity;
	}
	return false;
}

UCItem* UCInventoryComponent::FindItem(UCItem* Item) const
{
	if (Item)
	{
		for (auto& InvItem : Items)
		{
			if(InvItem && InvItem->GetClass() == Item->GetClass())
			{
				return InvItem;
			}
		}
	}

	return nullptr;
}

UCItem* UCInventoryComponent::FindItemByClass(TSubclassOf<class UCItem> ItemClass) const
{
	for (auto& InvItem : Items)
	{
		if (InvItem && InvItem->GetClass() == ItemClass)
		{
			return InvItem;
		}
	}
	return nullptr;
}

TArray<UCItem*> UCInventoryComponent::FindItemsByClass(TSubclassOf<class UCItem> ItemClass) const
{
	TArray<UCItem*> ItemsOfClass;

	for (auto& InvItem : Items)
	{
		if (InvItem && InvItem->GetClass()->IsChildOf(ItemClass))
		{
			ItemsOfClass.Add(InvItem);
		}
	}

	return ItemsOfClass;
}

float UCInventoryComponent::GetCurrentWeight() const
{
	float Weight = 0.f;

	for (auto& Item : Items)
	{
		if (Item)
		{
			Weight += Item->GetStackWeight();
		}
	}

	return Weight;
}

void UCInventoryComponent::SetWeightCapcity(const float NewWeightCapacity)
{
	WeightCapacity = NewWeightCapacity;
	OnInventoryUpdated.Broadcast();
}

void UCInventoryComponent::SetCapacity(const int32 NewCapacity)
{
	Capacity = NewCapacity;
	OnInventoryUpdated.Broadcast();
}

void UCInventoryComponent::ClientRefreshInventory_Implementation()
{
	OnInventoryUpdated.Broadcast();
}

void UCInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCInventoryComponent, Items);
}

bool UCInventoryComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (Channel->KeyNeedsToReplicate(0, ReplicatedItemsKey))
	{
		for (auto& Item : Items)
		{
			if (Channel->KeyNeedsToReplicate(Item->GetUniqueID(), Item->RepKey))
			{
				bWroteSomething |= Channel->ReplicateSubobject(Item, *Bunch, *RepFlags);
			}
		}
	}

	return bWroteSomething;
}

UCItem* UCInventoryComponent::AddItem(UCItem* Item)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		UCItem* NewItem = NewObject<UCItem>(GetOwner(), Item->GetClass());
		NewItem->SetQuantity(Item->GetQuantity());
		NewItem->OwningInventory = this;
		NewItem->AddedToInventory(this);
		Items.Add(NewItem);
		NewItem->MarkDirtyForReplication();

		return NewItem;
	}

	return nullptr;
}

void UCInventoryComponent::OnRep_Items()
{
	OnInventoryUpdated.Broadcast();
}

FItemAddResult UCInventoryComponent::TryAddItem_Internal(UCItem* Item)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		const int32 AddAmount = Item->GetQuantity();

		if (Items.Num() + 1 > GetCapacity())
		{
			return FItemAddResult::AddedNone(AddAmount, LOCTEXT("InventoryCapacityFullText", "Couldn't add item to Inventory. Inventory is full"));
		}

		if (!FMath::IsNearlyZero(Item->Weight))
		{
			if (GetCurrentWeight() + Item->Weight > GetWeightCapacity())
			{
				return FItemAddResult::AddedNone(AddAmount, LOCTEXT("InventoryTooMuchWeightText", "Couldn't add item to Inventory. Carrying too much weight"));
			}
		}

		//�������� ������ ���� �� �ִٸ� �̹� �����ϰ� �ִ����� ������ �߰��ϴ°��� check�Ѵ�.
		if (Item->bStackable)
		{
			// MaxStackSize�� �ѱ��� �ʰ��Ѵ�.
			ensure(Item->GetQuantity() <= Item->MaxStackSize);

			if (UCItem* ExistingItem = FindItem(Item))
			{
				if (ExistingItem->GetQuantity() < ExistingItem->MaxStackSize)
				{
					//�߰��� �׸��� ���� Ȯ��
					const int32 CapacityMaxAddAmount = ExistingItem->MaxStackSize - ExistingItem->GetQuantity();
					int32 ActualAddAmount = FMath::Min(AddAmount, CapacityMaxAddAmount);

					FText ErrorText = LOCTEXT("InventoryErrorText", "Couldn't add all of the item to your inventory.");

					//�츮�� ����� �� �ִ� ���Կ� ���� ����
					if (!FMath::IsNearlyZero(Item->Weight))
					{
						//���Է� ���� ������ �� �ִ� ǰ���� �ִ� �ݾ��� ����
						const int32 weightMaxAddAmount = FMath::FloorToInt((WeightCapacity - GetCurrentWeight()) / Item->Weight);
						ActualAddAmount = FMath::Min(ActualAddAmount, weightMaxAddAmount);

						if (ActualAddAmount < AddAmount)
						{
							ErrorText = FText::Format(LOCTEXT("InventoryTooMuchWeightText", "Could't add entire stack of (ItemName) to Inventory"), Item->ItemDisplayName);
						}
					}
					else if (ActualAddAmount < AddAmount)
					{
						//ǰ�� ���԰� ���� ������ �� ���� ��� �뷮 ������ �ִ� ��
						ErrorText = FText::Format(LOCTEXT("InventoryCapacityFullText", "Couldn't add entire stack of {ItemName} to Inventory. Inventory was full."), Item->ItemDisplayName);
					}
					//�̺��� �ƹ��͵� ������ ������
					if (ActualAddAmount <= 0)
					{
						return FItemAddResult::AddedNone(AddAmount, LOCTEXT("InventoryErrorText", "Couldn't add item to inventory"));
					}

					ExistingItem->SetQuantity(ExistingItem->GetQuantity() + ActualAddAmount);

					// ��Ե� �ִ� ���� ũ�⺸�� �� ���� �׸��� ��´ٸ� ������ ����
					ensure(ExistingItem->GetQuantity() <= ExistingItem->MaxStackSize);

					if (ActualAddAmount < AddAmount)
					{
						return FItemAddResult::AddedSome(AddAmount, ActualAddAmount, ErrorText);
					}
					else
					{
						return FItemAddResult::AddedAll(AddAmount);
					}
				}
				else
				{
					return FItemAddResult::AddedNone(AddAmount, FText::Format(LOCTEXT("InvemtoryFullStackText", "Couldn't add {ItemName}. You already have a full stackof this item"), Item->ItemDisplayName));
				}
			}
			else
			{
				// �� �׸��� �����Ƿ� ��ü ������ �߰�
				AddItem(Item);

				return FItemAddResult::AddedAll(AddAmount);
			}
		}
		else // item�� stack���� �ƴҶ�
		{
			// stack���� �ƴϸ� ������ 1�̿����Ѵ�.
			ensure(Item->GetQuantity() == 1);

			AddItem(Item);

			return FItemAddResult::AddedAll(AddAmount);
		}
	}

	//AddItem�� Ŭ���̾�Ʈ���� ȣ��Ǿ�� �� �˴ϴ�.
	check(false);
	return FItemAddResult::AddedNone(-1, LOCTEXT("ErrorMessage", ""));
}

#undef LOCTEXT_NAMESPACE