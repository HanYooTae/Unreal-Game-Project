#include "CharacterComponents/CStatusComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Global.h"

UCStatusComponent::UCStatusComponent()
{

}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void UCStatusComponent::ChangeMoveSpeed_Implementation(EWalkSpeedType InType)
{
	UCharacterMovementComponent* movementComp = CHelpers::GetComponent<UCharacterMovementComponent>(GetOwner());
	CheckNull(movementComp);

	movementComp->MaxWalkSpeed = WalkSpeed[(int8)InType];
}

void UCStatusComponent::DecreaseHealth_Implementation(float InAmount)
{
	CurrentHealth -= InAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);
}

void UCStatusComponent::IncreaseHealth_Implementation(float InAmount)
{
	CurrentHealth += InAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);
}
