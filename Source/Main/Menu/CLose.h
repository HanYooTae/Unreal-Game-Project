#pragma once

#include "CoreMinimal.h"
#include "Menu/CMenuBase.h"
#include "Blueprint/UserWidget.h"
#include "CLose.generated.h"

UCLASS()
class MAIN_API UCLose : public UCMenuBase
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
