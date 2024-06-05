#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData_Spawned.h"
#include "CActionData.generated.h"

UCLASS()
class MAIN_API UCActionData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	void BeginPlay(class ACharacter* InOwnerCharacter, UCActionData_Spawned** OutSpawned);

private:
	FString GetCustomLabel(class ACharacter* InOwnerCharacter, FString InMiddleName);

public:
	UPROPERTY(EditAnywhere, Category = "Weapon")
		TSubclassOf<class ACWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, Category = "Equipment")
		TSubclassOf<class ACEquipment> EquipmentClass;

	UPROPERTY(EditAnywhere, Category = "DoAction")
		TSubclassOf<class ACDoAction> DoActionClass;

	UPROPERTY(EditAnywhere, Category = "Equipment")
		FEquipmentData EquipmentData;

	// 콤보 공격이 있을 수 있기 때문에 TArray 사용
	UPROPERTY(EditAnywhere, Category = "DoAction")
		TArray<FDoActionData> DoActionDatas;

	class ACWeapon* Weapon;
	class ACEquipment* Equipment;
	class ACDoAction* DoAction;
};
