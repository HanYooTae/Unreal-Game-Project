#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBeginOverlapSignature, class ACharacter*, InAttacker, class AActor*, InCauser, class ACharacter*, InOtherCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FEndOverlapSignature, class ACharacter*, InAttacker, class AActor*, InCauser, class ACharacter*, InOtherCharacter);

UCLASS()
class MAIN_API ACWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	ACWeapon();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
		virtual void Attachment(FName InSocketName);

	UFUNCTION(BlueprintCallable)
		virtual void AttachmentToComp(class USceneComponent* InComponent, FName InSocketName);

public:		// 무기 장착 or 해제 시 socket변경
	UFUNCTION(BlueprintImplementableEvent)
		void OnEquip();

	UFUNCTION(BlueprintImplementableEvent)
		void OnUnequip();

public:
	void OnCollisions();
	void OffCollisions();

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* Weapon;

public:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

public:
	FBeginOverlapSignature OnBeginOverlap;
	FEndOverlapSignature OnEndOverlap;

private:	// Component
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

private:
	TArray<class UShapeComponent*> Collisions;
};