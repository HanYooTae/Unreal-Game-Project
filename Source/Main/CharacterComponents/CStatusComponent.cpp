#include "CharacterComponents/CStatusComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Global.h"

UCStatusComponent::UCStatusComponent()
{

}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCStatusComponent::ChangeMoveSpeed(EWalkSpeedType InType)
{
	UCharacterMovementComponent* movementComp = CHelpers::GetComponent<UCharacterMovementComponent>(GetOwner());
	CheckNull(movementComp);

	movementComp->MaxWalkSpeed = WalkSpeed[(int8)InType];
}