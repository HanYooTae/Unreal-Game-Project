#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Enemy.generated.h"

UCLASS()
class MAIN_API ACDoAction_Enemy : public ACDoAction
{
	GENERATED_BODY()

public:
	//UFUNCTION(Reliable, Server)
		virtual void DoAction() override;

	//UFUNCTION(NetMulticast, Reliable)
		void DoAction_RPC();

	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

public:
	virtual void OnBeginOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) override;

	virtual void OnEndOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) override;

	FORCEINLINE void EnableCombo() { bCanCombo = true; }
	FORCEINLINE void DisableCombo() { bCanCombo = false; }

private:
	UFUNCTION()
		void RestoreTimeDilation();

private:
	int32 ComboCount;
	bool bCanCombo;
	bool bSucceed;
};
