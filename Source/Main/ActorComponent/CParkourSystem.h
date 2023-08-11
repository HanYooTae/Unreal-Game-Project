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
	void Vault();				// �÷��̾� VŰ�� ������ ����Ǵ� �Լ�
	void HighOrNormal();		// ������ Ȯ���ϴ� �Լ�
	void High_Parkour();		// ������ ������ �����ϴ� �Լ�
	void Normal_Parkour();		// ������ �����ʾ����� �����ϴ� �Լ�

	void NextMontageYorN();		// Climb Montage������ ���� JumpingDownFromWall�� ���� ���������� if��
	void LastCollision();

public:
	class ACharacter* Owner;
	class UCAnimInstance* Anim;

private:
	FVector WallLocation;	// ��ġ���� ����
	FVector WallNormal;		// normal vector ���庯��
	FVector WallHeight;		// ���� ���� ����
	FVector WallHeight2;	// ���� ���� ����2

private:
	bool Canclimb;			// �ö󰥼� �ִ��������� bool����
	bool ShouldPlayerClimb;	// ������ ���� parkour ���� bool����
	bool IsWallThick;		// ��ü�� �β��� �����ϰ� �ö��� �Ѿ���� ���� bool����
	bool IsClimbing;		// parkour�� �ϰ� �ִ°��� ���� bool����
};
