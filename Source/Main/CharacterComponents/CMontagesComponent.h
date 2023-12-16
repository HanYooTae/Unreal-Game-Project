#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterComponents/CStateComponent.h"
#include "Engine/DataTable.h"
#include "CMontagesComponent.generated.h"

USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		EStateType Type;

	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditDefaultsOnly)
		float PlayRate = 1.f;

	UPROPERTY(EditDefaultsOnly)
		FName StartSection;

	UPROPERTY(EditDefaultsOnly)
		bool bCanMove;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAIN_API UCMontagesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCMontagesComponent();

protected:
	virtual void BeginPlay() override;

public:

	UFUNCTION(NetMulticast, Reliable)
		void PlayHitted();
	void PlayHitted_Implementation();

	UFUNCTION(NetMulticast, Reliable)
		void PlayDead();
	void PlayDead_Implementation();

private:
	UFUNCTION(NetMulticast, Reliable)
		void PlayMontage(EStateType InStateType);
	void PlayMontage_Implementation(EStateType InStateType);

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* DataTable;
		
private:
	FMontageData* Datas[(int8)EStateType::Max];
};
