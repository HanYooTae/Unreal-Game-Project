#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CMenuBase.generated.h"

UCLASS()
class MAIN_API UCMenuBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Attach();		// AddtoViewport, inputGameMode, MouseCursor, Mouse Hidden
	void Detach();		// Reverse
};
