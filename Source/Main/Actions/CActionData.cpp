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

	DoAction = nullptr;
	if (!!DoActionClass)
	{
		DoAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDoAction>(DoActionClass, transform, InOwnerCharacter);

		DoAction->SetDatas(DoActionDatas);
		DoAction->SetActorLabel(GetCustomLabel(InOwnerCharacter, "DoAction"));

		UGameplayStatics::FinishSpawningActor(DoAction, transform);

		// Equipment에 있는 주소가 DoAction으로 참조됨 (같은 주소를 사용함)
		if (!!Equipment)
		{
			DoAction->SetEquippedThis(Equipment->IsEquippedThis());
		}

		if (!!Weapon)
		{
			/*Weapon->OnBeginOverlap.AddDynamic(DoAction, &ACDoAction::OnBeginOverlap);
			Weapon->OnEndOverlap.AddDynamic(DoAction, &ACDoAction::OnEndOverlap);*/
		}
	}

	(*OutSpawned) = NewObject<UCActionData_Spawned>();
	(*OutSpawned)->Weapon = Weapon;
	(*OutSpawned)->Equipment = Equipment;
	(*OutSpawned)->DoAction = DoAction;
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
