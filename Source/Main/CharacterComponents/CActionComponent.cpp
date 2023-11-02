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

	// Unarmed ����
	Datas[(int32)EActionType::Unarmed]->GetEquipment();

	ChangeType(EActionType::Unarmed);
}

void UCActionComponent::SetFistMode()
{
}

void UCActionComponent::SetSwordMode()
{
	SetMode(EActionType::Sword);
}

void UCActionComponent::SetSniperMode()
{
}

void UCActionComponent::SetMagicBallMode()
{
}

void UCActionComponent::SetWarpMode()
{
}

void UCActionComponent::SetStormMode()
{
}

void UCActionComponent::SetMode(EActionType InNewType)
{
	// ���� Ű�� 2�� ������ ��
	if (Type == InNewType)
	{
		SetUnarmedMode();

		return;
	}

	// Unarmed�� �ƴ� Type�� �����ϰ� �־��ٸ�
	else if (IsUnarmedMode() == false)
	{
		// ���� ���� ���� ����
		if (!!Datas[(int32)Type] && !!Datas[(int32)Type]->GetEquipment())
			Datas[(int32)Type]->GetEquipment();
	}
	// ���ο� ���� ����
	if (!!Datas[(int32)InNewType] && !!Datas[(int32)InNewType]->GetEquipment())
		Datas[(int32)InNewType]->GetEquipment();

	ChangeType(InNewType);
}

void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType prev = Type;
	Type = InNewType;

	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prev, InNewType);
}
