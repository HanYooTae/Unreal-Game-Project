#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterComponents/CStateComponent.h"
#include "CEnemy.generated.h"

UCLASS()
class MAIN_API ACEnemy : public ACharacter 
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	void Hitted();
	void Dead();

	UFUNCTION()
		void End_Dead();

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

	

private: // Health Widget
	class UWidgetComponent* HealthWidget;

protected: //Actor Component
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCActionComponent* Action;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

private:
	UPROPERTY(EditAnywhere)
		float LaunchValue = 25.f;

	UPROPERTY(EditAnywhere)
		bool bVisibleNameWidget = false;

private:
	class UMaterialInstanceDynamic* UpperMaterial;
	class UMaterialInstanceDynamic* LowerMaterial;

	class ACharacter* Attacker;
	class AActor* Causer;
	float DamageValue;
};
