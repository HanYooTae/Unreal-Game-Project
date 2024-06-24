#include "Inventory/CItem.h"
#include "../ActorComponent/CInventoryComponent.h"
#include "Net/UnrealNetwork.h"
#include "CPlayer/CPlayer.h"

#define LOCTEXT_NAMESPACE "Item"

void UCItem::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCItem, Quantity);
}

bool UCItem::IsSupportedForNetworking() const
{
	return true;
}

#if WITH_EDITOR
void UCItem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName ChangeedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (ChangeedPropertyName == GET_MEMBER_NAME_CHECKED(UCItem, Quantity))
	{
		Quantity = FMath::Clamp(Quantity, 1, bStackable ? MaxStackSize : 1);
	}
}
#endif

UCItem::UCItem()
{
	ItemDisplayName = LOCTEXT("ItemName", "Item");
	UseActionText = LOCTEXT("ItemUseActionText", "Use");
	Weight = 0.f;
	bStackable = true;
	Quantity = 1;
	MaxStackSize = 2;
	RepKey = 0;
}

void UCItem::OnRep_Quantity()
{
	OnItemModified.Broadcast();
}

void UCItem::SetQuantity(const int32 NewQuantity)
{
	if (NewQuantity != Quantity)
	{
		Quantity = FMath::Clamp(NewQuantity, 0, bStackable ? MaxStackSize : 1);
		MarkDirtyForReplication();
	}
}

bool UCItem::ShouldShowInInventory() const
{
	return true;
}

void UCItem::Use(ACPlayer* Character)
{
	if (UCInventoryComponent* Inventory = Character->PlayerInventory)
	{
		Inventory->ConsumeItem(this, 1);
	}
}

void UCItem::MarkDirtyForReplication()
{
	//이 개체를 복제용으로 표시
	++RepKey;

	//복제할 어레이 표시
	if (OwningInventory)
	{
		++OwningInventory->ReplicatedItemsKey;
	}

}

#undef LOCTEXT_NAMEPSPACE