#include "Items/CItem.h"

UCItem::UCItem()
{
	Weight = 1.f;
	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");
}

void UCItem::Use(ACPlayer* Character)
{

}
