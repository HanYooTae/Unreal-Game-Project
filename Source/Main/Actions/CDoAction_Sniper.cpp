#include "Actions/CDoAction_Sniper.h"
#include "Actions/CWeapon_Sniper.h"
#include "Actions/CAim.h"
#include "Particles/ParticleSystem.h"
#include "CharacterComponents/CActionComponent.h"
#include "CharacterComponents/CStateComponent.h"
#include "CharacterComponents/CStatusComponent.h"
#include "CPlayer/CPlayer.h"
#include "GameFramework/Character.h"
#include "MatineeCameraShake.h"
#include "CBullet.h"
#include "Global.h"

ACDoAction_Sniper::ACDoAction_Sniper()
{
	// Initialize Camera Shake
	CHelpers::GetClass(&ShakeClass, "Blueprint'/Game/Character/CameraShake/BP_FireShake.BP_FireShake_C'");

	//Mesh = Sniper->GetWeapon();

	// Initialize Sniper DoAction Particle
	/*CHelpers::GetAsset(&MuzzleParticle, "ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Muzzleflash.VFX_Muzzleflash'");
	CHelpers::GetAsset(&EjectParticle, "ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Eject_bullet.VFX_Eject_bullet'");*/

	// Initialize Sniper DoAction Sound
	/*CHelpers::GetAsset(&FireSound, "SoundCue'/Game/Sounds/S_RifleShoot_Cue.S_RifleShoot_Cue'");*/
}

void ACDoAction_Sniper::BeginPlay()
{
	Super::BeginPlay();
	Aim = NewObject<UCAim>();
	Aim->BeginPlay(OwnerCharacter);

	ActionComp = CHelpers::GetComponent<UCActionComponent>(OwnerCharacter);
	ActionComp->OnActionTypeChanged.AddDynamic(this, &ACDoAction_Sniper::AbortByTypeChanged);
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

	// Camera Shake
	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	if (!!player)
	{
		APlayerController* controller = player->GetController<APlayerController>();
		if (!!controller)
			controller->PlayerCameraManager->StartCameraShake(ShakeClass);
	}

	// Play Effect
	//UGameplayStatics::SpawnEmitterAttached(MuzzleParticle, Mesh, "Muzzle");
	//UGameplayStatics::SpawnEmitterAttached(EjectParticle, Mesh, "ADSSocket");
	//UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, muzzleLocation);

	bullet->FinishSpawning(transform);

	// 충돌처리
	bullet->OnBeginOverlap.AddDynamic(this, &ACDoAction_Sniper::OnBulletBeginOverlap);

}

void ACDoAction_Sniper::End_DoAction()
{
	StateComp->SetIdleMode();
	StatusComp->SetMove();
}

void ACDoAction_Sniper::OnAim_Implementation()
{
	CheckNull(Aim);
	Aim->On();
}

void ACDoAction_Sniper::OffAim_Implementation()
{
	CheckNull(Aim);
	Aim->Off();
}

void ACDoAction_Sniper::OnBulletBeginOverlap(FHitResult hitResult)
{
	FDamageEvent damageEvent;
	hitResult.GetActor()->TakeDamage
	(
		Datas[0].power,
		damageEvent,
		OwnerCharacter->GetController(),
		this
	);
}

void ACDoAction_Sniper::AbortByTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	CheckFalse(Aim->IsAvailable());
	CheckFalse(Aim->IsZooming());
	Aim->Off();
}