#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unarmed, Fist, Sword, Sniper, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChangedSignature, EActionType, InPrevType, EActionType, InNewType);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MAIN_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UCActionComponent();

protected:
	virtual void BeginPlay() override;

public:		// Get Action
	UFUNCTION(BlueprintPure)
		class UCActionData_Spawned* GetCurrentData() { return Datas[(int32)Type]; }

	UFUNCTION(BlueprintPure)
		class UCActionData* GetCurrentDataAsset() { return DataAssets[(int32)Type]; }

public:		// bool Type
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() { return Type == EActionType::Unarmed; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsFistMode() { return Type == EActionType::Fist; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsOneHandMode() { return Type == EActionType::Sword; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsSniperMode() { return Type == EActionType::Sniper; }

public:		// Set Action
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
		void SetUnarmedMode();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
		void SetFistMode();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
		void SetSwordMode();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
		void SetSniperMode();

private:
	void SetMode(EActionType InNewType);		// 무기를 들고 있을 때 같은 무기를 호출하면 Unarmed로 회귀시켜주는 함수
	void ChangeType(EActionType InNewType);

public:		// Get Assets
	void DoAction();
	void DoAim(bool InPressed);

public:
	UPROPERTY(BlueprintAssignable)
		FActionTypeChangedSignature OnActionTypeChanged;

public:
	UPROPERTY(EditDefaultsOnly)
		class UCActionData* DataAssets[(int32)EActionType::Max];

private:
	EActionType Type;

	UPROPERTY()
		class UCActionData_Spawned* Datas[(int32)EActionType::Max];
};
