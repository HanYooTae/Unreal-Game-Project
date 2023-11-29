#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actions/CWeapon.h"
#include "CWeapon_Sword.generated.h"

UCLASS()
class MAIN_API ACWeapon_Sword : public ACWeapon
{
	GENERATED_BODY()
	
public:	
	ACWeapon_Sword();

protected:
	virtual void BeginPlay() override;

public:
	void Attachment(FName InSocketName) override;
};
