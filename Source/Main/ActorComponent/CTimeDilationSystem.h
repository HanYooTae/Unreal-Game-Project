#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTimeDilationSystem.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MAIN_API UCTimeDilationSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	UCTimeDilationSystem();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
		float Adjust_Time = 1;
};
