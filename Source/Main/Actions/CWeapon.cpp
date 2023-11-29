#include "Actions/CWeapon.h"
#include "GameFramework/Character.h"
#include "Global.h"

ACWeapon::ACWeapon()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
}

void ACWeapon::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	Super::BeginPlay();
	
}

//void ACWeapon::AttachmentToComp(class USceneComponent* InComponent, class ACharacter* OwnerCharacter, FName InSocketName)
//{
//	InComponent->AttachToComponent
//	(
//		OwnerCharacter->GetMesh(),
//		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
//		InSocketName
//	);
//}