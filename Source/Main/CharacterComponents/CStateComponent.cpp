#include "CharacterComponents/CStateComponent.h"

UCStateComponent::UCStateComponent()
{
}


void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCStateComponent::SetIdleMode_Implementation()
{
	ChangeType(EStateType::Idle);
}

void UCStateComponent::SetEquipMode_Implementation()
{
	ChangeType(EStateType::Equip);
}

void UCStateComponent::SetActionMode_Implementation()
{
	ChangeType(EStateType::Action);
}

void UCStateComponent::SetHittedMode_Implementation()
{
	ChangeType(EStateType::Hitted);
}

void UCStateComponent::SetDeadMode_Implementation()
{
	ChangeType(EStateType::Dead);
}

void UCStateComponent::ChangeType_Implementation(EStateType InNewType)
{
	EStateType prev = Type;
	Type = InNewType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(prev, InNewType);
}