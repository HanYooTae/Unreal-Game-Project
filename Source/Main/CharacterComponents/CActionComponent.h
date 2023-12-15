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

public:		// Set Action NetMulticast
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
		void SetUnarmedMode();
		void SetUnarmedMode_Implementation();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
		void SetFistMode();
		void SetFistMode_Implementation();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
		void SetSwordMode();
		void SetSwordMode_Implementation();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
		void SetSniperMode();
		void SetSniperMode_Implementation();

private:
	UFUNCTION(NetMulticast, Reliable)
		void SetMode(EActionType InNewType);		// 무기를 들고 있을 때 같은 무기를 호출하면 Unarmed로 회귀시켜주는 함수
		void SetMode_Implementation(EActionType InNewType);

	UFUNCTION(NetMulticast, Reliable)
		void ChangeType(EActionType InNewType);
	void ChangeType_Implementation(EActionType InNewType);

public:		// Get Assets
	UFUNCTION(NetMulticast, Reliable)
		void DoAction();
	void DoAction_Implementation();
	
	UFUNCTION(NetMulticast, Reliable)
		void DoAim(bool InPressed);
	void DoAim_Implementation(bool InPressed);


	UFUNCTION(NetMulticast, Reliable)
		void OffAllCollisions();		// 죽었을 때 무기 충돌체 Off
	void OffAllCollisions_Implementation();		// 죽었을 때 무기 충돌체 Off
	
	UFUNCTION(NetMulticast, Reliable)
		void End_Dead();
	void End_Dead_Implementation();

public:
	UPROPERTY(BlueprintAssignable)
		FActionTypeChangedSignature OnActionTypeChanged;

public:
	UPROPERTY(EditDefaultsOnly)
		class UCActionData* DataAssets[(int32)EActionType::Max];

private:
	EActionType Type;

	class UCActionData_Spawned* Datas[(int32)EActionType::Max];
};
