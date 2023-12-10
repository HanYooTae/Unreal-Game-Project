#include "CPlayer/CAnimInstance.h"
#include "Global.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterComponents/CActionComponent.h"

UCAnimInstance::UCAnimInstance()
{
	Falling = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> CLIMB(TEXT("AnimMontage'/Game/Character/Heraklios/Montage/Parkour/Braced_Hang_To_Crouch_Montage.Braced_Hang_To_Crouch_Montage'"));
	if (CLIMB.Succeeded())
		ClimbMontage = CLIMB.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> JumpingDown(TEXT("AnimMontage'/Game/Character/Heraklios/Montage/Parkour/Jumping_Down_Montage.Jumping_Down_Montage'"));
	if (JumpingDown.Succeeded())
		JumpingDownMontage = JumpingDown.Object;

}

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());

	UCActionComponent* actionComp = CHelpers::GetComponent<UCActionComponent>(OwnerCharacter);
	CheckNull(actionComp);

	actionComp->OnActionTypeChanged.AddDynamic(this, &UCAnimInstance::OnActionTypeChanged);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
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

void UCAnimInstance::OnActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	ActionType = InNewType;
}