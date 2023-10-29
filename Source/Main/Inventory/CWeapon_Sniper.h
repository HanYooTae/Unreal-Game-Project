#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory/CWeapon.h"
#include "CWeapon_Sniper.generated.h"

UCLASS()
class MAIN_API ACWeapon_Sniper : public ACWeapon
{
	GENERATED_BODY()
	
public:	
	ACWeapon_Sniper();

protected:
	virtual void BeginPlay() override;

public:
	void Attachment(class ACharacter* OwnerCharacter, FName InSocketName) override;
};
