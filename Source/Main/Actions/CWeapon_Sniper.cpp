#include "Actions/CWeapon_Sniper.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"

ACWeapon_Sniper::ACWeapon_Sniper()
{
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WEAPON(TEXT("SkeletalMesh'/Game/ItemAsset/Weapons/M14/Mesh/SK_M14.SK_M14'"));
	if (WEAPON.Succeeded())
	{
		Weapon->SetSkeletalMesh(WEAPON.Object);
	}

	CHelpers::CreateSceneComponent(this, &GunshotParticle, "GunshotParticle", Weapon);
	GunshotParticle->SetupAttachment(Weapon, "Muzzle");
	GunshotParticle->bAutoActivate = false;

	CHelpers::CreateSceneComponent(this, &CartridgeParticle, "CartridgeParticle", Weapon);
	CartridgeParticle->SetupAttachment(Weapon, "LeftHandGripPoint");
	CartridgeParticle->bAutoActivate = false;

	SetReplicates(true);
}

void ACWeapon_Sniper::BeginPlay()
{
	Super::BeginPlay();
}

void ACWeapon_Sniper::Attachment(FName InSocketName)
{
	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		InSocketName
	);
}


