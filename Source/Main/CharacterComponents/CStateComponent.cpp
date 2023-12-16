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

void UCStateComponent::SetIdleMode_Server_Implementation()
{
	SetIdleMode();
}

void UCStateComponent::SetEquipMode_Server_Implementation()
{
	SetEquipMode();
}

void UCStateComponent::SetActionMode_Server_Implementation()
{
	SetActionMode();
}

void UCStateComponent::SetHittedMode_Server_Implementation()
{
	SetHittedMode();
}

void UCStateComponent::SetDeadMode_Server_Implementation()
{
	SetDeadMode();
}

void UCStateComponent::ChangeType(EStateType InNewType)
{
	EStateType prev = Type;
	Type = InNewType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(prev, InNewType);
}