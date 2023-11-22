#include "Actions/CDoAction_Sniper.h"
#include "Actions/CAim.h"
#include "CharacterComponents/CActionComponent.h"
#include "CharacterComponents/CStateComponent.h"
#include "CharacterComponents/CStatusComponent.h"
#include "GameFramework/Character.h"
#include "CBullet.h"
#include "Global.h"

void ACDoAction_Sniper::BeginPlay()
{
	Super::BeginPlay();
	Aim = NewObject<UCAim>();
	Aim->BeginPlay(OwnerCharacter);
}

void ACDoAction_Sniper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Aim->Tick(DeltaTime);
}

void ACDoAction_Sniper::DoAction()
{
	CheckFalse(Datas.Num() > 0);

	CheckFalse(StateComp->IsIdleMode());
	StateComp->SetActionMode();

	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
}

void ACDoAction_Sniper::Begin_DoAction()
{
	// Spawn Projectile
	CheckNull(Datas[0].ProjectileClass);

	// 카메라의 위치, 회전
	FVector location;
	FRotator rotation;
	OwnerCharacter->GetController()->GetPlayerViewPoint(location, rotation);

	FVector handSocketLocation = OwnerCharacter->GetMesh()->GetSocketLocation("hand_r");
	FVector cameraDirection = rotation.Vector();

	location += cameraDirection * ((handSocketLocation - location) | cameraDirection);

	FTransform transform = Datas[0].EffectTransform;
	transform.AddToTranslation(location);

	transform.SetRotation(FQuat(OwnerCharacter->GetControlRotation()));		// != OwnerCharacter->GetActorForwardVector()->Rotation()

	ACBullet* bullet = GetWorld()->SpawnActorDeferred<ACBullet>
		(
			Datas[0].ProjectileClass,
			transform,
			OwnerCharacter,
			OwnerCharacter,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);

	// 충돌처리
	

	bullet->FinishSpawning(transform);
}

void ACDoAction_Sniper::End_DoAction()
{
	StateComp->SetIdleMode();
	StatusComp->SetMove();
}

void ACDoAction_Sniper::OnAim()
{
	CheckNull(Aim);
	Aim->On();
}

void ACDoAction_Sniper::OffAim()
{
	CheckNull(Aim);
	Aim->Off();
}
