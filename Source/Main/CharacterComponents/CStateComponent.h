#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Equip, Action, Hitted, Dead, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChangedSignature, EStateType, InPrevType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAIN_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStateComponent();

protected:
	virtual void BeginPlay() override;

public:		// Get StateType
	bool IsIdleMode() { return Type == EStateType::Idle; }
	bool IsEquipMode() { return Type == EStateType::Equip; }
	bool IsActionMode() { return Type == EStateType::Action; }
	bool IsHittedMode() { return Type == EStateType::Hitted; }
	bool IsDeadMode() { return Type == EStateType::Dead; }
	
	EStateType GetType() { return Type; }

public:		// Set StateType
	UFUNCTION(NetMulticast, Reliable)
		void SetIdleMode();
	void SetIdleMode_Implementation();
	
	UFUNCTION(NetMulticast, Reliable)
		void SetEquipMode();
	void SetEquipMode_Implementation();
	
	UFUNCTION(NetMulticast, Reliable)
		void SetActionMode();
	void SetActionMode_Implementation();
	
	UFUNCTION(NetMulticast, Reliable)
		void SetHittedMode();
	void SetHittedMode_Implementation();
	
	UFUNCTION(NetMulticast, Reliable)
		void SetDeadMode();
	void SetDeadMode_Implementation();

	UFUNCTION(NetMulticast, Reliable)
		void ChangeType(EStateType InNewType);
	void ChangeType_Implementation(EStateType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
		FStateTypeChangedSignature OnStateTypeChanged;

private:
	EStateType Type;
};