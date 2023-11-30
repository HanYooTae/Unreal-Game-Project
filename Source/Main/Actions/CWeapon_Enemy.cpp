#include "Actions/CWeapon_Enemy.h"
#include "Global.h"
#include "GameFramework/Character.h"

ACWeapon_Enemy::ACWeapon_Enemy()
{
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WEAPON(TEXT("SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Silly_Weapons/Blade_ChickenBlade/SK_Blade_ChickenBlade.SK_Blade_ChickenBlade'"));
	if (WEAPON.Succeeded())
	{
		Weapon->SetSkeletalMesh(WEAPON.Object);
	}

	SetReplicates(true);
}

void ACWeapon_Enemy::BeginPlay()
{
	Super::BeginPlay();
}

void ACWeapon_Enemy::Attachment(FName InSocketName)
{
	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		InSocketName
	);
}
