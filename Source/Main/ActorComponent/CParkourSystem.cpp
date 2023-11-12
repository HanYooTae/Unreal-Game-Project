#include "ActorComponent/CParkourSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/CapsuleComponent.h"
#include "../CPlayer/CAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "../CPlayer/CPlayer.h"
#include "Engine/World.h"
#include "Global.h"

UCParkourSystem::UCParkourSystem()
{
}

void UCParkourSystem::Parkour_Implementation()
{
	Vault();
}

void UCParkourSystem::Vault_Implementation()
{
	if (IsClimbing == false)
	{
		Owner = Cast<ACPlayer>(GetOwner());
		CheckNull(Owner);

		FVector PlayerLocation = Owner->GetActorLocation();
		FVector Start = PlayerLocation + FVector(0, 0, -44.0f);

		FVector End = Owner->GetActorForwardVector() * 70.0f + Start;

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
		ObjectTypes.Add(WorldStatic);
		TArray<AActor*> ignoreActor;
		FLinearColor TraceColor;
		FLinearColor TraceHitColor;
		FHitResult hitResult;

		bool Result = UKismetSystemLibrary::LineTraceSingleForObjects // player ���� ��ü �ν�trace
		(
			GetWorld(),
			Start,
			End,
			ObjectTypes,					// ����Ѽ� ��� �⺻�� ����
			true,
			ignoreActor,					// ����Ѽ� ��� �⺻�� ����
			EDrawDebugTrace::ForDuration,
			hitResult,
			true,
			TraceColor.Red,
			TraceHitColor.Green,
			5.0f
		);

		if (Result == true)
		{
			WallLocation = hitResult.Location;	// ���� ��ü�� ��ġ ����
			WallNormal = hitResult.Normal;		// ���� ��ü�� normal vector ����
			CLog::Print("Result Good");
			CLog::Print("WallLocation z: " + FString::FromInt(WallLocation.Z));
			FVector SAndE = ((Owner->GetActorForwardVector() * 10.0f) + WallLocation); // �÷��̾� ���濡�� �����ϸ� �������� �������� Ʈ���̼� ����
			FVector Start1 = SAndE + FVector(0, 0, 200);
			FVector End1 = Start1 - FVector(0, 0, 200);
			FHitResult hitResult1;


			bool Result1 = UKismetSystemLibrary::LineTraceSingleForObjects
			(
				GetWorld(),
				Start1,
				End1,
				ObjectTypes,					// ����Ѽ� ��� �⺻�� ����
				true,
				ignoreActor,					// ����Ѽ� ��� �⺻�� ����
				EDrawDebugTrace::ForDuration,
				hitResult1,
				true,
				TraceColor.Red,
				TraceHitColor.Green,
				5.0f
			);

			if (Result1 == true)
			{
				WallHeight = hitResult1.Location;	// ��ü�� ���� ����
				CLog::Print("Result1 Good");
				CLog::Print("WallHeight : " + FString::FromInt(WallHeight.Z));
				FVector SAndE2 = ((Owner->GetActorForwardVector() * 50.0f) + WallLocation);	// ��ü�� �β��� �˱����� �ι�° ����trace
				FVector Start2 = SAndE2 + FVector(0, 0, 250);
				FVector End2 = Start2 - FVector(0, 0, 300);
				FHitResult hitResult2;

				bool Result2 = UKismetSystemLibrary::LineTraceSingleForObjects
				(
					GetWorld(),
					Start2,
					End2,
					ObjectTypes,					// ����Ѽ� ��� �⺻�� ����
					true,
					ignoreActor,					// ����Ѽ� ��� �⺻�� ����
					EDrawDebugTrace::ForDuration,
					hitResult2,
					true,
					TraceColor.Red,
					TraceHitColor.Green,
					5.0f
				);

				if (Result2 == true)
				{
					WallHeight2 = hitResult2.Location; // �ι�° ����trace ��ġ����
					CLog::Print("WallHeight2 : " + FString::FromInt(WallHeight2.Z));
					CLog::Print("Result2 Good");

					FVector HminusH2 = WallHeight - WallHeight2;
					CLog::Print("HminusH2.x : " + FString::FromInt(HminusH2.X));
					CLog::Print("HminusH2.y" + FString::FromInt(HminusH2.Y));
					if (HminusH2.Z > 30)
					{
						IsWallThick = false;
					}
					else
					{
						IsWallThick = true;
					}

					float HminusL = WallHeight.Z - WallLocation.Z;
					CLog::Print("HminusL: " + FString::FromInt(HminusL));

					if (HminusL >= 60)
					{
						Jump();
					}
				}
				else
				{
					IsWallThick = false;

					float HminusL = WallHeight.Z - WallLocation.Z;
					CLog::Print("HminusL: " + FString::FromInt(HminusL));

					if (HminusL >= 60)
					{
						Jump();
					}
				}
			}
		}
	}
}



void UCParkourSystem::Jump_Implementation()
{
	Owner = Cast<ACPlayer>(GetOwner());
	CheckNull(Owner);

	CLog::Print("JUMPIN!!!!!!!!!!!!!!!!!!!!!!!!");
	FVector JStart = Owner->GetActorLocation() + FVector(0);
	FVector JEnd = JStart + (Owner->GetActorForwardVector() * 70);
	FHitResult hitResult;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
	ObjectTypes.Add(WorldStatic);
	TArray<AActor*> ignoreActor;
	FLinearColor TraceColor;
	FLinearColor TraceHitColor;

	bool Result = UKismetSystemLibrary::LineTraceSingleForObjects // ������ ���� �ö󰥼� �ִ������θ� �Ǵ��ϴ� trace
	(
		GetWorld(),
		JStart,
		JEnd,
		ObjectTypes,					// ����Ѽ� ��� �⺻�� ����
		true,
		ignoreActor,					// ����Ѽ� ��� �⺻�� ����
		EDrawDebugTrace::ForDuration,
		hitResult,
		true,
		TraceColor.Red,
		TraceHitColor.Green,
		5.0f
	);

	if (Result == true)
	{
		Canclimb = true;

		FVector Start = Owner->GetActorLocation();
		FVector End = Start + FVector(0, 0, 200);

		bool Result1 = UKismetSystemLibrary::LineTraceSingleForObjects // ���� parkour�� ���� �Ѿ���Ҷ� player�������� ��ֹ��̾����� Ȯ��
		(
			GetWorld(),
			Start,
			End,
			ObjectTypes,					// ����Ѽ� ��� �⺻�� ����
			true,
			ignoreActor,					// ����Ѽ� ��� �⺻�� ����
			EDrawDebugTrace::ForDuration,
			hitResult,
			true,
			TraceColor.Red,
			TraceHitColor.Green,
			5.0f
		);

		CLog::Print("CanClimb = true");
	}
	else
	{
		FVector Start = Owner->GetActorLocation();
		FVector End = Start = FVector(0, 0, 200);

		bool Result1 = UKismetSystemLibrary::LineTraceSingleForObjects // ���� parkour�� ���� �Ѿ���Ҷ� player�������� ��ֹ��̾����� Ȯ��
		(
			GetWorld(),
			Start,
			End,
			ObjectTypes,					// ����Ѽ� ��� �⺻�� ����
			true,
			ignoreActor,					// ����Ѽ� ��� �⺻�� ����
			EDrawDebugTrace::ForDuration,
			hitResult,
			true,
			TraceColor.Red,
			TraceHitColor.Green,
			5.0f
		);

		CLog::Print("CanClimb = false");
	}

	if (Canclimb == true)
	{
		IsClimbing = true;
		Owner->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Owner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

		//float yaw = Owner->GetActorForwardVector().Z;
		//FRotator Rotation = FRotator(Owner->GetActorRotation().Roll, Owner->GetActorRotation().Pitch, yaw);
		//Owner->SetActorRotation(Rotation);

		FVector Location = (Owner->GetActorForwardVector() * 5.0f) + Owner->GetActorLocation();
		Owner->SetActorLocation(Location);

		FVector Z = WallHeight - FVector(0, 0, 44);
		FVector Location2 = FVector(Owner->GetActorLocation().X, Owner->GetActorLocation().Y, Z.Z);
		Owner->SetActorLocation(Location2);
		CLog::Print("Good");

		auto AnimInstance = Cast<UCAnimInstance>(Owner->GetMesh()->GetAnimInstance());
		CheckNull(AnimInstance);

		AnimInstance->PlayClimbMontage();
		//->Montage_Play(Anim->ClimbMontage, 1.0f); //error

		FTimerHandle timerHandle;
		GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &UCParkourSystem::NextMontageYorN, 1.13f);
			
	}

}

void UCParkourSystem::NextMontageYorN_Implementation()
{
	auto AnimInstance = Cast<UCAnimInstance>(Owner->GetMesh()->GetAnimInstance());
	CheckNull(AnimInstance);

	if (IsWallThick == true)
	{
		Owner->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Owner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		IsClimbing = false;		
	}
	else
	{
		AnimInstance->PlayJumpingDownMontage();
		FTimerHandle timerHandle;
		GetWorld()->GetTimerManager().SetTimer(timerHandle, 1.0f, false);
		Owner->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Owner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		IsClimbing = false;
	}
}






