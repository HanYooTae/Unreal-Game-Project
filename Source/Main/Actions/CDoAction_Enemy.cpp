#include "Actions/CDoAction_Enemy.h"
#include "GameFramework/Character.h"
#include "CharacterComponents/CStateComponent.h"
#include "CharacterComponents/CStatusComponent.h"
#include "Global.h"

void ACDoAction_Enemy::DoAction()
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

	StateComp->SetActionMode();

	// 첫 번째 액션(공격) 몽타주 재생
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
}

void ACDoAction_Enemy::DoAction_RPC()
{
}

void ACDoAction_Enemy::Begin_DoAction()
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

void ACDoAction_Enemy::End_DoAction()
{
	Super::End_DoAction();

	OwnerCharacter->StopAnimMontage(Datas[ComboCount].AnimMontage);

	ComboCount = 0;

	StateComp->SetIdleMode();
	StatusComp->SetMove();
}

void ACDoAction_Enemy::OnBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
}

void ACDoAction_Enemy::OnEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
}

void ACDoAction_Enemy::RestoreTimeDilation()
{
}
