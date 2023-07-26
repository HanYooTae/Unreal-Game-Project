#include "ActorComponent/CParkourSystem.h"
#include "../CPlayer/CPlayer.h"
#include "Global.h"
#include "Engine/World.h"

UCParkourSystem::UCParkourSystem()
{
}

void UCParkourSystem::Vault()
{
	FVector PlayerLocation = player->GetActorLocation(); //- FVector(0, 0, 44.0f); ลอมü
	FVector Start = PlayerLocation;

	FVector End = player->GetActorForwardVector() * 70.0f + Start;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
	ObjectTypes.Add(WorldStatic);
	TArray<AActor*> ignoreActor;
	FHitResult hitResult;
	FLinearColor TraceColor;
	FLinearColor TraceHitColor;

	bool Result = UKismetSystemLibrary::LineTraceSingleForObjects
	(
		GetWorld(),
		Start, 
		End, 
		ObjectTypes, 
		true, 
		ignoreActor,
		EDrawDebugTrace::ForDuration,
		hitResult,
		true,
		TraceColor.Red,
		TraceHitColor.Green,
		5.0f
	);

	if (Result == true)
	{
		WallLocation = hitResult.Location;
		WallNormal = hitResult.Normal;
	}
	
}



