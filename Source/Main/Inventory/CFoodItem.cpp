#include "Inventory/CFoodItem.h"
#include "Global.h"

#define LOCTEXT_NAMESPACE "Item"

UCFoodItem::UCFoodItem()
{
	HealAmount = 20.f;
	UseActionText = LOCTEXT("ItemUseActionText", "Consume");
}

void UCFoodItem::Use(ACPlayer* Character)
{
	Super::Use(Character);
}

#undef LOCTEXT_NAMEPSPACE