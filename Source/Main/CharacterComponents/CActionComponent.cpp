#include "CActionComponent.h"
#include "Actions/CActionData_Spawned.h"
#include "Actions/CActionData.h"
#include "Actions/CEquipment.h"
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
	// ���� ����
	if (!!Datas[(int32)Type] && !!Datas[(int32)Type]->GetEquipment())
		Datas[(int32)Type]->GetEquipment()->Unequip();

	// Unarmed ����
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
			Datas[(int32)Type]->GetEquipment()->Unequip();
	}
	// ���ο� ���� ����
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

void UCActionComponent::DoAction()
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

void UCActionComponent::DoAim(bool InPressed)
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