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

	for (const auto& collision : Collisions)
	{
		collision->OnComponentBeginOverlap.AddDynamic(this, &ACWeapon::BeginOverlap);
		collision->OnComponentEndOverlap.AddDynamic(this, &ACWeapon::EndOverlap);
	}

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

void ACWeapon::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor_Server(OtherActor);
}

void ACWeapon::OtherActor_Server_Implementation(AActor* OtherActor)
{
	OtherActor_Client(OtherActor);
}

void ACWeapon::OtherActor_Client_Implementation(AActor* OtherActor)
{
	CheckTrue(OwnerCharacter == OtherActor);

	ACharacter* otherCharacter = Cast<ACharacter>(OtherActor);

	if (OnBeginOverlap.IsBound())
	{
		if (!!otherCharacter)
			OnBeginOverlap.Broadcast(OwnerCharacter, this, otherCharacter);
	}
}

void ACWeapon::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckTrue(OwnerCharacter == OtherActor);

	ACharacter* otherCharacter = Cast<ACharacter>(OtherActor);

	if (OnEndOverlap.IsBound())
	{
		if (!!otherCharacter)
			OnEndOverlap.Broadcast(OwnerCharacter, this, otherCharacter);
	}
}