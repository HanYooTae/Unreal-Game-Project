#include "Actions/CWeapon.h"
#include "GameFramework/Character.h"
#include "Global.h"
#include "Components/Shapecomponent.h"

ACWeapon::ACWeapon()
{
}

void ACWeapon::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	GetComponents(Collisions);

	OffCollisions();

	Super::BeginPlay();
	
}

void ACWeapon::Attachment(FName InSocketName)
{
	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		InSocketName
	);
}

void ACWeapon::AttachmentToComp(class USceneComponent* InComponent, FName InSocketName)
{
	InComponent->AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		InSocketName
	);
}

void ACWeapon::OnCollisions()
{
	for (const auto& collision : Collisions)
		collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACWeapon::OffCollisions()
{
	for (const auto& collision : Collisions)
		collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
