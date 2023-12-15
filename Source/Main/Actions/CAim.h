#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/TimelineComponent.h"
#include "CAim.generated.h"

UCLASS()
class MAIN_API UCAim : public UObject
{
	GENERATED_BODY()

public:
	UCAim();

	void BeginPlay(class ACharacter* InOwnerCharacter);
	void Tick(float DeltaTime);

	UFUNCTION(NetMulticast, Reliable)
		void On();
	void On_Implementation();

	UFUNCTION(NetMulticast, Reliable)
		void Off();
	void Off_Implementation();

public:
	FORCEINLINE bool IsAvailable() { return SpringArm != nullptr && Camera != nullptr; }
	FORCEINLINE bool IsZooming() { return bZooming; }
	
private:
	UFUNCTION()
		void Zooming(float Output);

public:
	FOnTimelineFloat OnTimeline;

private:
	class ACharacter* OwnerCharacter;
	class USpringArmComponent* SpringArm;
	class UCameraComponent* Camera;

	bool bZooming;

	class UCurveFloat* Curve;
	FTimeline Timeline;

	class ACHUD* HUD;
};