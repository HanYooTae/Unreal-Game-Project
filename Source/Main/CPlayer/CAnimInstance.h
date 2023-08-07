#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

UCLASS()
class MAIN_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UCAnimInstance();

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayClimbMontage();
	void PlayJumpingDownMontage();
	void PlayGettingUpMontage();
	void PlayVaultMontage();
protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		float Pitch;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		bool Falling;


public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* ClimbMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* JumpingDownMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* GettingUpMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* VaultMontage;

	EMontagePlayReturnType duration;

private:
	class ACharacter* OwnerCharacter;


};
