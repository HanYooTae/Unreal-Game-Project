#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Animation/AnimMontage.h"
#include "CParkourSystem.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MAIN_API UCParkourSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	UCParkourSystem();

	void Vault();		// 플레이어 V키를 누르면 실행되는 함수
	void JumpAndUp();	// 점프를 확인하는 함수
	void Jump();		// 점프를 했을때 실행하는 함수
	void Up();			// 점프를 하지않았을때 실행하는 함수

	void NextMontageYorN(); // Climb Montage다음에 나올 JumpingDownFromWall을 실행 할지에대한 if문
	void LastCollision();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Animation")
		UAnimMontage* Climb;

public:
	class ACPlayer* player;
	class ACharacter* Owner;
	class UCAnimInstance* Anim;

private:
	FVector WallLocation;	// 위치저장 변수
	FVector WallNormal;		// normal vector 저장변수
	FVector WallHeight;		// 높이 저장 변수
	FVector WallHeight2;	// 높이 저장 변수2

private:
	bool Canclimb;			// 올라갈수 있는지에대한 bool변수
	bool ShouldPlayerClimb;	// 점프를 통한 parkour 실행 bool변수
	bool IsWallThick;		// 물체의 두께를 학인하고 올라갈지 넘어갈지에 대한 bool번수
	bool IsClimbing;		// parkour를 하고 있는가에 대한 bool변수
	float Delay;
};
