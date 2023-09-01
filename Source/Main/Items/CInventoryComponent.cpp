#include "Items/CInventoryComponent.h"
#include "CItem.h"

UCInventoryComponent::UCInventoryComponent()
{
	Capacity = 20;
}

void UCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
}

bool UCInventoryComponent::AddItem(UCItem* Item)
{
	if (Items.Num() >= Capacity || !Item)
	{
		return false;
	}

	Item->OwningInventory = this;
	Item->World = GetWorld();
	Items.Add(Item);

	if(OnInventoryUpdated.IsBound())
		OnInventoryUpdated.Broadcast();

	return true;
}

bool UCInventoryComponent::RemoveItem(UCItem* Item)
{
	if (Item)
	{
		Item->OwningInventory = nullptr;
		Item->World = nullptr;
		Items.RemoveSingle(Item);
		if (OnInventoryUpdated.IsBound())
			OnInventoryUpdated.Broadcast();
		return true;
	}

	return false;
}

