#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CMenuBase.h"
#include "CBackQuitMenu.generated.h"

UCLASS()
class MAIN_API UCBackQuitMenu : public UCMenuBase
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

public:
	UFUNCTION()
		void BackButtonPressed();

	UFUNCTION()
		void QuitButtonPressed();

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* QuitButton;
};
