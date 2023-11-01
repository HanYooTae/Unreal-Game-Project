#include "Actions/CActionData.h"
#include "Actions/CWeapon.h"
#include "Actions/CEquipment.h"
#include "Actions/CDoAction.h"
#include "GameFramework/Character.h"
#include "Global.h"

void UCActionData::BeginPlay(class ACharacter* InOwnerCharacter, UCActionData_Spawned** OutSpawned)
{
	FTransform transform;

	ACWeapon* Weapon = nullptr;
	if (!!WeaponClass)
	{
		Weapon = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACWeapon>(WeaponClass, transform, InOwnerCharacter);

		Weapon->SetActorLabel(GetCustomLabel(InOwnerCharacter, "Weapon"));

		UGameplayStatics::FinishSpawningActor(Weapon, transform);
	}

	(*OutSpawned) = NewObject<UCActionData_Spawned>();
	(*OutSpawned)->Weapon = Weapon;
}

FString UCActionData::GetCustomLabel(ACharacter* InOwnerCharacter, FString InMiddleName)
{
	FString name;
	name.Append(InOwnerCharacter->GetActorLabel());
	name.Append("_");
	name.Append(InMiddleName);
	name.Append("_");

	name.Append(GetName().Replace(L"DA_", L""));

	return name;
}
