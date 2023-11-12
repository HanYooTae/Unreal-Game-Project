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

	UFUNCTION(Reliable, Server)
		void Parkour();
	UFUNCTION(NetMulticast, Reliable)
		void Vault();		// �÷��̾� VŰ�� ������ ����Ǵ� �Լ�
	UFUNCTION(NetMulticast, Reliable)
		void Jump();		// ������ ������ �����ϴ� �Լ�

	UFUNCTION(NetMulticast, Reliable)
		void NextMontageYorN(); // Climb Montage������ ���� JumpingDownFromWall�� ���� ���������� if��

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Animation")
		UAnimMontage* Climb;

public:
	class ACPlayer* player;
	class ACharacter* Owner;
	class UCAnimInstance* Anim;

private:
	FVector WallLocation;	// ��ġ���� ����
	FVector WallNormal;		// normal vector ���庯��
	FVector WallHeight;		// ���� ���� ����
	FVector WallHeight2;	// ���� ���� ����2

private:
	bool Canclimb;			// �ö󰥼� �ִ��������� bool����
	bool IsWallThick;		// ��ü�� �β��� �����ϰ� �ö��� �Ѿ���� ���� bool����
	bool IsClimbing;		// parkour�� �ϰ� �ִ°��� ���� bool����
	float Delay;
};
