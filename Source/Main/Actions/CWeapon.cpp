#include "Actions/CWeapon.h"
#include "GameFramework/Character.h"
#include "Global.h"

ACWeapon::ACWeapon()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}