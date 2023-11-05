#include "Actions/CActionData.h"
#include "Actions/CWeapon.h"
#include "Actions/CEquipment.h"
#include "Actions/CDoAction.h"
#include "GameFramework/Character.h"
#include "Global.h"

void UCActionData::BeginPlay(class ACharacter* InOwnerCharacter, UCActionData_Spawned** OutSpawned)
{
	FTransform transform;

	Weapon = nullptr;
	if (!!WeaponClass)
	{
		Weapon = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACWeapon>(WeaponClass, transform, InOwnerCharacter);

		Weapon->SetActorLabel(GetCustomLabel(InOwnerCharacter, "Weapon"));

		UGameplayStatics::FinishSpawningActor(Weapon, transform);
	}

	Equipment = nullptr;
	if (!!EquipmentClass)
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass, transform, InOwnerCharacter);
		
		Equipment->SetData(EquipmentData);
		Equipment->SetActorLabel(GetCustomLabel(InOwnerCharacter, "Equipment"));

		//Equipment->FinishSpawning()
		UGameplayStatics::FinishSpawningActor(Equipment, transform);

		if (!!Weapon)
		{
			Equipment->OnBeginEquip.AddDynamic(Weapon, &ACWeapon::OnEquip);
			Equipment->OnUnequip.AddDynamic(Weapon, &ACWeapon::OnUnequip);
		}
	}

	(*OutSpawned) = NewObject<UCActionData_Spawned>();
	(*OutSpawned)->Weapon = Weapon;
	(*OutSpawned)->Equipment = Equipment;
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
