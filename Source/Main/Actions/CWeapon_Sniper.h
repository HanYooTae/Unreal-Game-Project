#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actions/CWeapon.h"
#include "CWeapon_Sniper.generated.h"

UCLASS()
class MAIN_API ACWeapon_Sniper : public ACWeapon
{
	GENERATED_BODY()
	
public:	
	ACWeapon_Sniper();
	USkeletalMeshComponent* GetWeapon() { return Weapon; }

protected:
	virtual void BeginPlay() override;

public:
	void Attachment(FName InSocketName) override;

public:
	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* GunshotParticle;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* CartridgeParticle;
};
