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

public:
	FORCEINLINE void SetDatas(TArray<FDoActionData> InDatas) { Datas = InDatas; }
	FORCEINLINE void SetEquippedThis(const bool* InEquippedThis) { bEquippedThis = InEquippedThis; }

protected:
	TArray<FDoActionData> Datas;
	const bool* bEquippedThis;
};
