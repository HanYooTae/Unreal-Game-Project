#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.generated.h"

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
		virtual void Attachment(class ACharacter* OwnerCharacter, FName InSocketName) {};

	UFUNCTION(BlueprintCallable)
		virtual void AttachmentToComp(class USceneComponent* InComponent, class ACharacter* OwnerCharacter, FName InSocketName) {};

public:		// 무기 장착 or 해제 시 socket변경
	UFUNCTION(BlueprintImplementableEvent)
		void OnEquip();

	UFUNCTION(BlueprintImplementableEvent)
		void OnUnequip();

public:
	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* Weapon;

private:	// Component
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
};