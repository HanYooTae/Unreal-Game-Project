#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CActionData_Spawned.generated.h"

USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

	UPROPERTY(EditAnywhere)
		bool bPawnControl = true;
};

USTRUCT(BlueprintType)
struct FDoActionData : public FEquipmentData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		float power = 1.f;

	UPROPERTY(EditAnywhere)
		float HitStop;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* Effect;

	UPROPERTY(EditAnywhere)
		FTransform EffectTransform;

	/*UPROPERTY(EditAnywhere)
		TSubclassOf<UMatineeCameraShake> ShakeClass;*/

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACBullet> ProjectileClass;
};

UCLASS()
class MAIN_API UCActionData_Spawned : public UObject
{
	GENERATED_BODY()
		
public:		// UCActionData와의 접근성을 용이하게 하기 위하여 friend class로 지정
	friend class UCActionData;

public:
	FORCEINLINE class ACWeapon* GetWeapon() { return Weapon; }
	FORCEINLINE class ACEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE class ACDoAction* GetDoAction() { return DoAction; }

private:
	class ACWeapon* Weapon;
	class ACEquipment* Equipment;
	class ACDoAction* DoAction;
};
