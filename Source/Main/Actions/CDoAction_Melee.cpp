#include "Actions/CDoAction_Melee.h"
#include "GameFramework/Character.h"
#include "CharacterComponents/CStateComponent.h"
#include "CharacterComponents/CStatusComponent.h"
#include "Global.h"

void ACDoAction_Melee::DoAction()
{
	Super::DoAction();

	CheckFalse(Datas.Num() > 0);

	// Combo Flag
	if (bCanCombo == true)
	{
		bCanCombo = false;
		bSucceed = true;

		return;
	}
	
	// ���� ������������ return
	CheckFalse(StateComp->IsIdleMode());

	StateComp->SetActionMode();

	// ù ��° �׼�(����) ��Ÿ�� ���
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
}

void ACDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();

	CheckFalse(bSucceed);
	bSucceed = false;

	OwnerCharacter->StopAnimMontage();

	ComboCount++;
	ComboCount = FMath::Clamp(ComboCount, 0, Datas.Num() - 1);
	OwnerCharacter->PlayAnimMontage(Datas[ComboCount].AnimMontage, Datas[ComboCount].PlayRate, Datas[ComboCount].StartSection);
	Datas[ComboCount].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
}

void ACDoAction_Melee::End_DoAction()
{
	Super::End_DoAction();

	OwnerCharacter->StopAnimMontage(Datas[ComboCount].AnimMontage);

	ComboCount = 0;

	StateComp->SetIdleMode();
	StatusComp->SetMove();
}

void ACDoAction_Melee::OnBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnBeginOverlap(InAttacker, InCauser, InOtherCharacter);

	// �ٴ���Ʈ ����
	int32 hittedCharactersNum = HittedCharacters.Num();
	HittedCharacters.AddUnique(InOtherCharacter);
	CheckFalse(hittedCharactersNum < HittedCharacters.Num());

	// HitStop(�ش� ����� ������ or ������ ���� �ð����� ������ ������� �÷��̵�
	float hitStop = Datas[ComboCount].HitStop;
	if (FMath::IsNearlyZero(hitStop) == false)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.02f);
		UKismetSystemLibrary::K2_SetTimer(this, "RestoreTimeDilation", 0.02f * hitStop, false);
	}

	// Camera Shake
	TSubclassOf<UMatineeCameraShake> shakeClass = Datas[ComboCount].ShakeClass;
	if (!!shakeClass)
	{
		APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		CheckNull(controller);
		controller->PlayerCameraManager->StartCameraShake(shakeClass);
	}

	// Play Particles
	UParticleSystem* effect = Datas[ComboCount].Effect;
	CheckNull(effect);
	FTransform transform = Datas[ComboCount].EffectTransform;
	transform.AddToTranslation(InOtherCharacter->GetActorLocation());

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), effect, transform);
}

void ACDoAction_Melee::OnEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnEndOverlap(InAttacker, InCauser, InOtherCharacter);
}

void ACDoAction_Melee::RestoreTimeDilation()
{
	PrintLine();
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
}