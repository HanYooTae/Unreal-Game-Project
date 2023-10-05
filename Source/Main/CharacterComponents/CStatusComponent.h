#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"

UENUM(BlueprintType)
enum class EWalkSpeedType : uint8
{
	Sneak, Walk, Run, Max
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MAIN_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCStatusComponent();

protected:
	virtual void BeginPlay() override;

public:		// Change Character Movement Speed
	FORCEINLINE float GetSneakSpeed() { return WalkSpeed[(int8)EWalkSpeedType::Sneak]; }
	FORCEINLINE float GetWalkSpeed() { return WalkSpeed[(int8)EWalkSpeedType::Walk]; }
	FORCEINLINE float GetRunSpeed() { return WalkSpeed[(int8)EWalkSpeedType::Run]; }

	void ChangeMoveSpeed(EWalkSpeedType InType);

public:		// Change Can Move
	FORCEINLINE bool IsCanMove() { return bCanMove; }

	FORCEINLINE void SetMove() { bCanMove = true; }
	FORCEINLINE void SetStop() { bCanMove = false; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		TArray<float> WalkSpeed{ 200.f, 400.f, 600.f };

private:
	bool bCanMove = true;
};
