#pragma once

#include "CoreMinimal.h"
#include "Inventory/CItem.h"
#include "CWeaponsItem.generated.h"

UCLASS()
class MAIN_API UCWeaponsItem : public UCItem
{
	GENERATED_BODY()
	
public:
	UCWeaponsItem();

	virtual void Use(class ACPlayer* Character) override;

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		class AActor* Actor;


};
