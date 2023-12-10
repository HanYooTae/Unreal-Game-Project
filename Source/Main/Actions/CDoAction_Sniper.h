#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CharacterComponents/CActionComponent.h"
#include "CDoAction_Sniper.generated.h"

UCLASS()
class MAIN_API ACDoAction_Sniper : public ACDoAction
{
	GENERATED_BODY()
	
public:
	ACDoAction_Sniper();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

public:
	virtual void OnAim() override;
	virtual void OffAim() override;

private:
	UFUNCTION()
		void OnBulletBeginOverlap(FHitResult hitResult);

	UFUNCTION()
		void AbortByTypeChanged(EActionType InPrevType, EActionType InNewType);

private:
	UPROPERTY()
		class UCAim* Aim;

	class UCActionComponent* ActionComp;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMatineeCameraShake> ShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		class UParticleSystem* MuzzleParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		class UParticleSystem* EjectParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		class USoundCue* FireSound;

	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

private:
	class ACWeapon_Sniper* Sniper;
};
