#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CActionData.h"
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
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE void SetDatas(TArray<FDoActionData>& InDatas) { Datas = InDatas; }
	FORCEINLINE void SetEquippedThis(const bool* InEquippedThis) { bEquippedThis = InEquippedThis; }

public:
	virtual void DoAction() {};
	virtual void Begin_DoAction() {};
	virtual void End_DoAction() {};
	virtual void Abort() {};	// Storm전용 함수. Storm공격 중에 맞으면 공격중단

public:		// 원거리 무기 전용 함수
	virtual void OnAim() {};
	virtual void OffAim() {};

public:
	UFUNCTION()
		virtual void OnBeginOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) {};

	UFUNCTION()
		virtual void OnEndOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) {};

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* StatusComp;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* StateComp;

protected:
	TArray<FDoActionData> Datas;
	const bool* bEquippedThis;
};
