#include "ActorComponent/CParkourSystem.h"
#include "../CPlayer/CPlayer.h"
#include "Global.h"
#include "Engine/World.h"

UCParkourSystem::UCParkourSystem()
{
}

void UCParkourSystem::Vault()
{
	FVector PlayerLocation = GetOwner()->GetActorLocation(); 
	FVector Start = PlayerLocation + FVector(0, 0, -44.0f);

	FVector End = GetOwner()->GetActorForwardVector() * 70.0f + Start;

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
		CLog::Print("Result Good");
		FVector SAndE = ((GetOwner()->GetActorForwardVector() * 10.0f) + WallLocation);
		FVector Start1 = SAndE + FVector(0, 0, 200);
		FVector End1 = Start1 - FVector(0, 0, 200);
		FHitResult hitResult1;

		
		bool Result1 = UKismetSystemLibrary::LineTraceSingleForObjects
		(
			GetWorld(),
			Start1,
			End1,
			ObjectTypes,
			true,
			ignoreActor,
			EDrawDebugTrace::ForDuration,
			hitResult1,
			true,
			TraceColor.Red,
			TraceHitColor.Green,
			5.0f
		);
		
		if (Result1 == true)
		{
			WallHeight = hitResult1.Location;
			CLog::Print("Result1 Good");
			FVector SAndE2 = ((GetOwner()->GetActorForwardVector()  * 50.0f) + WallLocation);
			FVector Start2 = SAndE2 + FVector(0, 0, 250);
			FVector End2 = Start2 - FVector(0, 0, 300);
			FHitResult hitResult2;

			bool Result2 = UKismetSystemLibrary::LineTraceSingleForObjects
			(
				GetWorld(),
				Start2,
				End2,
				ObjectTypes,
				true,
				ignoreActor,
				EDrawDebugTrace::ForDuration,
				hitResult2,
				true,
				TraceColor.Red,
				TraceHitColor.Green,
				5.0f
			);
			
			if (Result2 == true)
			{
				WallHeight2 = hitResult2.Location;
				CLog::Print("Result2 Good");
			}
			else
			{
				IsWallThick = false;
			}
			

			FVector HminusH2 = WallHeight - WallHeight2;
			if (HminusH2.Z > 30)
			{
				IsWallThick = false;
			}
			else
			{
				IsWallThick = true;
			}
		}
		
		FVector HminusL = WallHeight - WallLocation;
		
		if (HminusL.Z > 60)
		{
			ShouldPlayerClimb = true;
		}
		else
		{
			ShouldPlayerClimb = false;
		}

	}
}
	




