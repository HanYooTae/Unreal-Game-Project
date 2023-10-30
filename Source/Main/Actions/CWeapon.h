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
	virtual void Attachment(class ACharacter* OwnerCharacter, FName InSocketName) {};

	virtual void AttachmentToComp(class USceneComponent* InComponent, class ACharacter* OwnerCharacter, FName InSocketName) {};

public:
	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* Weapon;
};