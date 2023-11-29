#pragma once

#include "CoreMinimal.h"
#include "Actions/CWeapon.h"
#include "CWeapon_Enemy.generated.h"

UCLASS()
class MAIN_API ACWeapon_Enemy : public ACWeapon
{
	GENERATED_BODY()
public:
	ACWeapon_Enemy();
	USkeletalMeshComponent* GetWeapon() { return Weapon; }

protected:
	virtual void BeginPlay() override;

public:
	void Attachment(FName InSocketName) override;
};
