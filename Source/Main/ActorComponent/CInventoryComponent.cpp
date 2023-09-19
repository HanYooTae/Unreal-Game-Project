#include "ActorComponent/CInventoryComponent.h"
#include "Net/UnrealNetwork.h"
#include "UObject/UObjectBase.h"
#include "Engine/ActorChannel.h"
#include "../Inventory/CPickup.h"
#include "Global.h"

#define LOCTEXT_NAMESPACE "Inventory"

UCInventoryComponent::UCInventoryComponent()
{
	// object를 복제 하기위한 함수 SetIsReplicated가 callstack이 일어나 SetIsReplicatedByDefault를 사용함
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

		//아이템을 떨어뜨린 후에는 마이너스가 나와야 함.
		ensure(!(Item->GetQuantity() - RemoveQuantity < 0)); // 표현식을 검증하여 실패하면 그 지점까지 이르는 콜스택을 생성합니다.

		//이제 이 항목이 없습니다.인벤토리에서 제거하세요.
		Item->SetQuantity(Item->GetQuantity() - RemoveQuantity);

		if (Item->GetQuantity() <= 0)
		{
			RemoveItem(Item);
			ClientRefreshInventory();
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
			if (InvItem && InvItem->GetClass() == Item->GetClass())
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

		//아이템이 스텍을 쌓을 수 있다면 이미 소유하고 있는지와 스텍을 추가하는것을 check한다.
		if (Item->bStackable)
		{
			// MaxStackSize를 넘기지 않게한다.
			ensure(Item->GetQuantity() <= Item->MaxStackSize);

			if (UCItem* ExistingItem = FindItem(Item))
			{
				if (ExistingItem->GetQuantity() < ExistingItem->MaxStackSize)
				{
					//추가할 항목의 양을 확인
					const int32 CapacityMaxAddAmount = ExistingItem->MaxStackSize - ExistingItem->GetQuantity();
					int32 ActualAddAmount = FMath::Min(AddAmount, CapacityMaxAddAmount);

					FText ErrorText = LOCTEXT("InventoryErrorText", "Couldn't add all of the item to your inventory.");

					//우리가 운반할 수 있는 무게에 따라 조정
					if (!FMath::IsNearlyZero(Item->Weight))
					{
						//무게로 인해 가져갈 수 있는 품목의 최대 금액을 구함
						const int32 weightMaxAddAmount = FMath::FloorToInt((WeightCapacity - GetCurrentWeight()) / Item->Weight);
						ActualAddAmount = FMath::Min(ActualAddAmount, weightMaxAddAmount);

						if (ActualAddAmount < AddAmount)
						{
							ErrorText = FText::Format(LOCTEXT("InventoryTooMuchWeightText", "Could't add entire stack of (ItemName) to Inventory"), Item->ItemDisplayName);
						}
					}
					else if (ActualAddAmount < AddAmount)
					{
						//품목 무게가 없고 감당할 수 없는 경우 용량 문제가 있는 것
						ErrorText = FText::Format(LOCTEXT("InventoryCapacityFullText", "Couldn't add entire stack of {ItemName} to Inventory. Inventory was full."), Item->ItemDisplayName);
					}
					//이벤에 아무것도 넣을수 없을때
					if (ActualAddAmount <= 0)
					{
						return FItemAddResult::AddedNone(AddAmount, LOCTEXT("InventoryErrorText", "Couldn't add item to inventory"));
					}

					ExistingItem->SetQuantity(ExistingItem->GetQuantity() + ActualAddAmount);

					// 어떻게든 최대 스택 크기보다 더 많은 항목을 얻는다면 문제가 있음
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
				// 이 항목이 없으므로 전체 스택을 추가
				AddItem(Item);

				return FItemAddResult::AddedAll(AddAmount);
			}
		}
		else // item이 stack형이 아닐때
		{
			// stack형이 아니면 수량은 1이여야한다.
			ensure(Item->GetQuantity() == 1);

			AddItem(Item);

			return FItemAddResult::AddedAll(AddAmount);
		}
	}

	//AddItem은 클라이언트에서 호출되어서는 안 됩니다.
	check(false);
	return FItemAddResult::AddedNone(-1, LOCTEXT("ErrorMessage", ""));
}

#undef LOCTEXT_NAMESPACE