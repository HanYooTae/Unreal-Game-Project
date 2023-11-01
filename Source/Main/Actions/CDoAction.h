#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDoAction.generated.h"

UCLASS()
class MAIN_API ACDoAction : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDoAction();

protected:
	virtual void BeginPlay() override;

};
