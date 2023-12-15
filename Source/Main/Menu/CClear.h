#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu/CMenuBase.h"
#include "CClear.generated.h"

UCLASS()
class MAIN_API UCClear : public UCMenuBase
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

public:
	UFUNCTION()
		void QuitButtonPressed();

private:

	UPROPERTY(meta = (BindWidget))
		class UButton* QuitButton;
};
