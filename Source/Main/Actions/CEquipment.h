#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actions/CActionData.h"
#include "CEquipment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginEquipSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnequipSignature);

UCLASS()
class MAIN_API ACEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE void SetData(const FEquipmentData& InData) { EquipmentData = InData; }
	//FORCEINLINE const bool* IsEquippedThis() { return &bEquippedThis; }

public:
	// Play Draw Montage
	UFUNCTION(BlueprintNativeEvent)
		void Equip();
	void Equip_Implementation();

	// Attach to hand socket
	UFUNCTION(BlueprintNativeEvent)
		void Begin_Equip();
	void Begin_Equip_Implementation();

	// Set State Idle
	UFUNCTION(BlueprintNativeEvent)
		void End_Equip();
	void End_Equip_Implementation();

	// 무기를 넣으면 orient를 켜주는 역할
	UFUNCTION(BlueprintNativeEvent)
		void Unequip();
	void Unequip_Implementation();

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;
	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* StateComp;
	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* StatusComp;

public:
	UPROPERTY(BlueprintAssignable)
		FBeginEquipSignature OnBeginEquip;

	UPROPERTY(BlueprintAssignable)
		FUnequipSignature OnUnequip;

private:
	FEquipmentData EquipmentData;

	//bool bEquippedThis;		// 무기가 장착이 되어있는지 아닌지 판단하는 변수

};
