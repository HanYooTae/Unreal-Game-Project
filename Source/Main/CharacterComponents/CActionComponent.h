#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CActionComponent.generated.h"

UCLASS()
class MAIN_API ACActionComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	ACActionComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
