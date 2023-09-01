#include "Items/FoodCItem.h"
#include "CInventoryComponent.h"
#include "../CPlayer/CPlayer.h"

void UFoodCItem::Use(class ACPlayer* Character)
{
	if(Character)
		Character->Health += HealthToHeal;

	if (OwningInventory)
	{
		OwningInventory->RemoveItem(this);
	}
}
