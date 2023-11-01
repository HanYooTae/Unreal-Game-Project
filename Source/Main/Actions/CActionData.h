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
	UPROPERTY(EditAnywhere, Category = "Attachment")
		TSubclassOf<class ACWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, Category = "Equipment")
		TSubclassOf<class ACEquipment> EquipmentClass;

	UPROPERTY(EditAnywhere, Category = "Equipment")
		FEquipmentData EquipmentData;

	UPROPERTY(EditAnywhere, Category = "DoAction")
		TSubclassOf<class ACDoAction> DoActionClass;

	UPROPERTY(EditAnywhere, Category = "DoAction")
		TArray<FDoActionData> DoActionDatas;
};
