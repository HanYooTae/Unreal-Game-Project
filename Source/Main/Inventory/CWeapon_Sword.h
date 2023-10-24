#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon_Sword.generated.h"

UCLASS()
class MAIN_API ACWeapon_Sword : public AActor
{
	GENERATED_BODY()
	
public:	
	ACWeapon_Sword();

protected:
	virtual void BeginPlay() override;

public:
	void Attachment(class ACharacter* OwnerCharacter, FName InSocketName);

public:
	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* Weapon;

};
