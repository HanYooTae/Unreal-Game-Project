#include "CActionComponent.h"
#include "Actions/CActionData_Spawned.h"
#include "Actions/CActionData.h"
#include "Actions/CEquipment.h"
#include "Actions/CWeapon.h"
#include "GameFramework/Character.h"
#include "Global.h"
#include "Actions/CDoAction.h"

UCActionComponent::UCActionComponent()
{

}

void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	ACharacter* ownerCharacter = Cast<ACharacter>(GetOwner());

	for (int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		if (!!DataAssets[i])
			DataAssets[i]->BeginPlay(ownerCharacter, &Datas[i]);
	}
}

void UCActionComponent::SetUnarmedMode_Implementation()
{
	// 무기 해제
	if (!!Datas[(int32)Type] && !!Datas[(int32)Type]->GetEquipment())
		Datas[(int32)Type]->GetEquipment()->Unequip();

	// Unarmed 장착
	//Datas[(int32)EActionType::Unarmed]->GetEquipment()->Equip();

	ChangeType(EActionType::Unarmed);
}

void UCActionComponent::SetFistMode_Implementation()
{
	SetMode(EActionType::Fist);
}

void UCActionComponent::SetSwordMode_Implementation()
{
	SetMode(EActionType::Sword);
}

void UCActionComponent::SetSniperMode_Implementation()
{
	SetMode(EActionType::Sniper);
}

void UCActionComponent::SetMode_Implementation(EActionType InNewType)
{
	// 같은 키를 2번 눌렀을 때
	if (Type == InNewType)
	{
		SetUnarmedMode();

		return;
	}

	// Unarmed가 아닌 Type을 장착하고 있었다면
	else if (IsUnarmedMode() == false)
	{
		// 이전 무기 장착 해제
		if (!!Datas[(int32)Type] && !!Datas[(int32)Type]->GetEquipment())
			Datas[(int32)Type]->GetEquipment()->Unequip();
	}
	// 새로운 무기 장착
	if (!!Datas[(int32)InNewType] && !!Datas[(int32)InNewType]->GetEquipment())
		Datas[(int32)InNewType]->GetEquipment()->Equip();

	ChangeType(InNewType);
}

void UCActionComponent::ChangeType_Implementation(EActionType InNewType)
{
	EActionType prev = Type;
	Type = InNewType;

	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prev, InNewType);
}

void UCActionComponent::DoAction_Implementation()
{
	CheckTrue(IsUnarmedMode());

	if (!!GetCurrentData())
	{
		ACDoAction* doAction = GetCurrentData()->GetDoAction();
		if (!!doAction)
		{
			doAction->DoAction();
		}
	}
}

void UCActionComponent::DoAim_Implementation(bool InPressed)
{
	CheckTrue(IsUnarmedMode());

	if (!!GetCurrentData())
	{
		ACDoAction* doAction = GetCurrentData()->GetDoAction();
		if (!!doAction)
		{
			InPressed ? doAction->OnAim() : doAction->OffAim();
		}
	}
}

void UCActionComponent::OffAllCollisions_Implementation()
{
	for (const auto& data : Datas)
	{
		if (data == nullptr)
			continue;

		if (data->GetWeapon() == nullptr)
			continue;

		data->GetWeapon()->OffCollisions();
	}
}

void UCActionComponent::End_Dead_Implementation()
{
	for (int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		if (!!Datas[i] && !!Datas[i]->GetEquipment())
			Datas[i]->GetEquipment()->Destroy();

		if (!!Datas[i] && !!Datas[i]->GetWeapon())
			Datas[i]->GetWeapon()->Destroy();

		if (!!Datas[i] && !!Datas[i]->GetDoAction())
			Datas[i]->GetDoAction()->Destroy();
	}
}
