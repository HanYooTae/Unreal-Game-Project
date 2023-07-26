#include "ActorComponent/CParkourSystem.h"
#include "Global.h"
#include "Engine/World.h"

UCParkourSystem::UCParkourSystem()
{

}

void UCParkourSystem::Vault()
{
	FHitResult hitResult;
	FCollisionObjectQueryParams params;


	bool Result1 = GetWorld()->LineTraceSingleByObjectType
	(
		FHitResult& OutHit,
		FVector& Start,
		FVector& End,
		FCollisionObjectQueryParams & ObjectQueryParams,
		FCollisionQueryParams & Params
	);
}



