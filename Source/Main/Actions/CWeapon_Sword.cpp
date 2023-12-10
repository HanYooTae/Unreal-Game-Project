#include "Actions/CWeapon_Sword.h"
#include "Global.h"
#include "GameFramework/Character.h"

ACWeapon_Sword::ACWeapon_Sword()
{
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WEAPON(TEXT("SkeletalMesh'/Game/ItemAsset/Weapons/Sword/SK_Straight_Sword.SK_Straight_Sword'"));
	if (WEAPON.Succeeded())
	{
		Weapon->SetSkeletalMesh(WEAPON.Object);
	}

	SetReplicates(true);
}

void ACWeapon_Sword::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACWeapon_Sword::Attachment(FName InSocketName)
{
	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		InSocketName
	);
}


