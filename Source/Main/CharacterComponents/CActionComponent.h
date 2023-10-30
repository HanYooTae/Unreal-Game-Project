#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unarmed, Fist, Sword, Sniper, MagicBall, Warp, Storm, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChangedSignature, EActionType, InPrevType, EActionType, InNewType);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MAIN_API ACActionComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	ACActionComponent();

protected:
	virtual void BeginPlay() override;

public:		// Get Action
	UFUNCTION(BlueprintPure)
		class UCActionData_Spawned* GetCurrentData() { return Datas[(int32)Type]; }

	UFUNCTION(BlueprintPure)
		class UCActionData* GetCurrentDataAsset() { return DataAssets[(int32)Type]; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() { return Type == EActionType::Unarmed; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsFistMode() { return Type == EActionType::Fist; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsOneHandMode() { return Type == EActionType::Sword; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsSniperMode() { return Type == EActionType::Sniper; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsMagicBallMode() { return Type == EActionType::MagicBall; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsWarpMode() { return Type == EActionType::Warp; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsStormMode() { return Type == EActionType::Storm; }

public:		// Set Action
	UFUNCTION(BlueprintCallable)
		void SetUnarmedMode();

	UFUNCTION(BlueprintCallable)
		void SetFistMode();

	UFUNCTION(BlueprintCallable)
		void SetSwordMode();

	UFUNCTION(BlueprintCallable)
		void SetSniperMode();

	UFUNCTION(BlueprintCallable)
		void SetMagicBallMode();

	UFUNCTION(BlueprintCallable)
		void SetWarpMode();

	UFUNCTION(BlueprintCallable)
		void SetStormMode();

private:
	void SetMode(EActionType InNewType);		// ���⸦ ��� ���� �� ���� ���⸦ ȣ���ϸ� Unarmed�� ȸ�ͽ����ִ� �Լ�
	void ChangeType(EActionType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
		FActionTypeChangedSignature OnActionTypeChanged;

private:
	UPROPERTY(EditDefaultsOnly)
		class UCActionData* DataAssets[(int32)EActionType::Max];

private:
	EActionType Type;

	UPROPERTY()
		class UCActionData_Spawned* Datas[(int32)EActionType::Max];
};