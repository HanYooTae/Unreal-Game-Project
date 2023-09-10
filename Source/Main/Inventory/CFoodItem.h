#pragma once

#include "CoreMinimal.h"
#include "Inventory/CItem.h"
#include "CFoodItem.generated.h"

UCLASS()
class MAIN_API UCFoodItem : public UCItem
{
	GENERATED_BODY()
	
public:

	UCFoodItem();

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Healing")
		float HealAmount;

	virtual void Use(class ACPlayer* Character) override;
};
