#pragma once

#include "CoreMinimal.h"
#include "Items/CItem.h"
#include "FoodCItem.generated.h"

UCLASS()
class MAIN_API UFoodCItem : public UCItem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item", meta = (ClampMin = 0.00))
		float HealthToHeal;

protected:

	virtual void Use(class ACPlayer* Character) override;
};
