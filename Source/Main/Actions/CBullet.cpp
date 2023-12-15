#include "Actions/CBullet.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "particles/ParticleSystemComponent.h"

ACBullet::ACBullet()
{
	CHelpers::CreateSceneComponent(this, &Sphere, "Sphere");
	CHelpers::CreateSceneComponent(this, &Particle, "Particle", Sphere);

	CHelpers::CreateActorComponent(this, &Projectile, "Projectile");

	InitialLifeSpan = 3.f;

	Projectile->InitialSpeed = 2000.f;
	Projectile->MaxSpeed = 4000.f;
	Projectile->ProjectileGravityScale = 0.f;
}

void ACBullet::BeginPlay()
{
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACBullet::OnComponentBeginOverlap);

	Super::BeginPlay();
}

void ACBullet::OnComponentBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OtherActor == GetOwner());

	// Play Impact Particles
	if (!!ImpactParticle)
	{
		FTransform transform = ImpactTransform;

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, transform);
	}

	// 데미지를 입히면
	if (OnBeginOverlap.IsBound())
		OnBeginOverlap.Broadcast(SweepResult);

	Destroy();
}