#include "Actions/CWeapon_Sniper.h"
#include "Global.h"
#include "GameFramework/Character.h"

ACWeapon_Sniper::ACWeapon_Sniper()
{
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WEAPON(TEXT("SkeletalMesh'/Game/ItemAsset/Weapons/M14/Mesh/SK_M14.SK_M14'"));
	if (WEAPON.Succeeded())
	{
		Weapon->SetSkeletalMesh(WEAPON.Object);
	}

	SetReplicates(true);
}

void ACWeapon_Sniper::BeginPlay()
{
	Super::BeginPlay();
}

void ACWeapon_Sniper::Attachment(class ACharacter* OwnerCharacter, FName InSocketName)
{
	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		InSocketName
	);
}


