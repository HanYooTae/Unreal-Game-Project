#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actions/CActionData.h"
#include "CEquipment.generated.h"

UCLASS()
class MAIN_API ACEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	ACEquipment();

protected:
	virtual void BeginPlay() override;

private:
	FEquipmentData EquipmentData;

};
