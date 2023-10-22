#include "Inventory/CWeaponsItem.h"
#include "Components/StaticMeshComponent.h"
#include "CPlayer/CPlayer.h"
#include "Global.h"

#define LOCTEXT_NAMESPACE "Item"

UCWeaponsItem::UCWeaponsItem()
{

}

void UCWeaponsItem::Use(ACPlayer* Character)
{
	Super::Use(Character);
}

#undef LOCTEXT_NAMEPSPACE