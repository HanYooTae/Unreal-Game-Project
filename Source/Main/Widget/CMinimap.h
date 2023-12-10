#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CMinimap.generated.h"

UCLASS()
class MAIN_API UCMinimap : public UUserWidget
{
	GENERATED_BODY()
	

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* TextBlock_52;
};
