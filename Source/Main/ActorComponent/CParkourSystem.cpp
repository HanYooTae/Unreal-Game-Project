#include "ActorComponent/CParkourSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
//#include "Components/PrimitiveComponent.h"
#include "Components/CapsuleComponent.h"
#include "../CPlayer/CAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "../CPlayer/CPlayer.h"
#include "Engine/World.h"
#include "Global.h"

void UCParkourSystem::Vault()
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

					FVector HminusH2 = WallHeight - WallHeight2;
					if (HminusH2.Z > 30)
					{
						IsWallThick = false;
					}
					else
					{
						IsWallThick = true;
					}

					float HminusL = WallHeight.Z - WallLocation.Z;

					if (HminusL >= 60)
					{
						ShouldPlayerClimb = true;
					}
					else
					{
						ShouldPlayerClimb = false;
					}

					HighOrNormal();
				}
				else
				{
					IsWallThick = false;

					float HminusL = WallHeight.Z - WallLocation.Z;

					if (HminusL >= 60)
					{
						ShouldPlayerClimb = true;
					}
					else
					{
						ShouldPlayerClimb = false;
					}

					HighOrNormal();
				}
			}
		}
	}
}

void UCParkourSystem::HighOrNormal()
{
	if (ShouldPlayerClimb == true)
	{
		High_Parkour();
	}
	else
	{
		Normal_Parkour();
	}
}

void UCParkourSystem::High_Parkour()
{
	Owner = Cast<ACPlayer>(GetOwner());
	CheckNull(Owner);

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

		bool Result1 = UKismetSystemLibrary::LineTraceSingleForObjects
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

	}

	if (Canclimb == true)
	{
		IsClimbing = true;
		Owner->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Owner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	
		FVector Location = (Owner->GetActorForwardVector() * 5.0f) + Owner->GetActorLocation();
		Owner->SetActorLocation(Location);
	
		FVector Z = WallHeight - FVector(0, 0, 44);
		FVector Location2 = FVector(Owner->GetActorLocation().X, Owner->GetActorLocation().Y, Z.Z);
		Owner->SetActorLocation(Location2);
	
		auto AnimInstance = Cast<UCAnimInstance>(Owner->GetMesh()->GetAnimInstance());
		CheckNull(AnimInstance);
		AnimInstance->PlayClimbMontage();
	
		FTimerHandle timerHandle;
		GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &UCParkourSystem::NextMontageYorN, 1.13f);
			
	}

}

void UCParkourSystem::NextMontageYorN()
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

void UCParkourSystem::Normal_Parkour()
{
	IsClimbing = true;
	auto AnimInstance = Cast<UCAnimInstance>(Owner->GetMesh()->GetAnimInstance());
	CheckNull(AnimInstance);
	Owner = Cast<ACPlayer>(GetOwner());
	CheckNull(Owner);
	Owner->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Owner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	if (IsWallThick == true)
	{
		FVector Location = (Owner->GetActorForwardVector() * 5.0f) + Owner->GetActorLocation();
		Owner->SetActorLocation(Location);
		AnimInstance->PlayGettingUpMontage();
	}
	else
	{			
		FVector Location = (Owner->GetActorForwardVector() * 10.0f) + Owner->GetActorLocation();
		Owner->SetActorLocation(Location);
		FVector Location2 = FVector(Owner->GetActorLocation().X, Owner->GetActorLocation().Y, WallHeight.Z - 30);
		Owner->SetActorLocation(Location2);
		AnimInstance->PlayVaultMontage();
	}
	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &UCParkourSystem::LastCollision, 1.0f);
	
	IsClimbing = false;
}

void UCParkourSystem::LastCollision()
{
	Owner->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Owner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}







