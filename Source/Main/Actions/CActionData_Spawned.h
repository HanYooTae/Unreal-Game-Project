#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CActionData_Spawned.generated.h"

UCLASS()
class MAIN_API UCActionData_Spawned : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE class ACWeapon_Sniper* GetSniper() { return Sniper; }

public:
	class ACWeapon_Sniper* Sniper;

};
