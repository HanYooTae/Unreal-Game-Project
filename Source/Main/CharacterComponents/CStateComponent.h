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
	//bool IsDashMode() { return Type == EStateType::Dash; }		// q키를 누르면 앞으로 텔레포트(대쉬)
	bool IsEquipMode() { return Type == EStateType::Equip; }
	bool IsActionMode() { return Type == EStateType::Action; }
	bool IsHittedMode() { return Type == EStateType::Hitted; }
	bool IsDeadMode() { return Type == EStateType::Dead; }
	
	EStateType GetType() { return Type; }

public:		// Set StateType
	void SetIdleMode();
	//void SetDashMode();
	void SetEquipMode();
	void SetActionMode();
	void SetHittedMode();
	void SetDeadMode();

	void ChangeType(EStateType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
		FStateTypeChangedSignature OnStateTypeChanged;

private:
	EStateType Type;
};