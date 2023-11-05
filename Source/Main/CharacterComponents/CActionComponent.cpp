#include "CActionComponent.h"
#include "Actions/CActionData_Spawned.h"
#include "Actions/CActionData.h"
#include "Actions/CEquipment.h"
#include "GameFramework/Character.h"

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

void UCActionComponent::SetUnarmedMode()
{
	if (!!Datas[(int32)Type] && !!Datas[(int32)Type]->GetEquipment())
		Datas[(int32)Type]->GetEquipment();

	// Unarmed 장착
	Datas[(int32)EActionType::Unarmed]->GetEquipment();

	ChangeType(EActionType::Unarmed);
}

void UCActionComponent::SetFistMode()
{
	SetMode(EActionType::Fist);
}

void UCActionComponent::SetSwordMode()
{
	SetMode(EActionType::Sword);
}

void UCActionComponent::SetSniperMode()
{
	SetMode(EActionType::Sniper);
}

void UCActionComponent::SetMagicBallMode()
{
	SetMode(EActionType::MagicBall);
}

void UCActionComponent::SetWarpMode()
{
	SetMode(EActionType::Warp);
}

void UCActionComponent::SetStormMode()
{
	SetMode(EActionType::Storm);
}

void UCActionComponent::SetMode(EActionType InNewType)
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

void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType prev = Type;
	Type = InNewType;

	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prev, InNewType);
}
