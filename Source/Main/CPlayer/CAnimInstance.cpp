#include "CPlayer/CAnimInstance.h"
#include "Global.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCAnimInstance::UCAnimInstance()
{
	Falling = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> CLIMB(TEXT("AnimMontage'/Game/Character/Animations/Parkour/ParkourAnimation/MQ_Climb_RM_Montage.MQ_Climb_RM_Montage'"));
	if (CLIMB.Succeeded())
		ClimbMontage = CLIMB.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> JumpingDown(TEXT("AnimMontage'/Game/Character/Animations/Parkour/ParkourAnimation/MQ_JumpingDownFromWall_RM_Montage.MQ_JumpingDownFromWall_RM_Montage'"));
	if (JumpingDown.Succeeded())
		JumpingDownMontage = JumpingDown.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> GettingUp(TEXT("AnimMontage'/Game/Character/Animations/Parkour/ParkourAnimation/MQ_GettingUp_RM_Montage.MQ_GettingUp_RM_Montage'"));
	if (GettingUp.Succeeded())
		GettingUpMontage = GettingUp.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Vault(TEXT("AnimMontage'/Game/Character/Animations/Parkour/ParkourAnimation/MQ_Vault_RM_Montage.MQ_Vault_RM_Montage'"));
	if (Vault.Succeeded())
		VaultMontage = Vault.Object;
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

void UCAnimInstance::PlayClimbMontage()
{
	if (!Montage_IsPlaying(ClimbMontage))
		Montage_Play(ClimbMontage, 1.0f);	
}

void UCAnimInstance::PlayJumpingDownMontage()
{
	if (!Montage_IsPlaying(JumpingDownMontage))
		Montage_Play(JumpingDownMontage, 1.0f);
}

void UCAnimInstance::PlayGettingUpMontage()
{
	if (!Montage_IsPlaying(GettingUpMontage))
		Montage_Play(GettingUpMontage, 1.0f);
}

void UCAnimInstance::PlayVaultMontage()
{
	if (!Montage_IsPlaying(VaultMontage))
		Montage_Play(VaultMontage, 1.0f);
}
