#include "CPlayer/CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCAnimInstance::UCAnimInstance()
{
	Falling = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> CLIMB(TEXT("AnimMontage'/Game/Character/Animations/Parkour/ParkourAnimation/MQ_Climb_RM_Montage.MQ_Climb_RM_Montage'"));
	if (CLIMB.Succeeded())
		ClimbMontage = CLIMB.Object;
}

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());
	Pitch = OwnerCharacter->GetBaseAimRotation().Pitch;
	Falling = OwnerCharacter->GetCharacterMovement()->IsFalling();
}
