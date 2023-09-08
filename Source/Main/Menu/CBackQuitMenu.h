#pragma once

#include "CoreMinimal.h"
#include "Menu/CMenuBase.h"
#include "CBackQuitMenu.generated.h"

UCLASS()
class MAIN_API UCBackQuitMenu : public UCMenuBase
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize() override;

public:
	// Should be Return to Game
	UFUNCTION()
		void BackButtonPressed();

	// Should be Return to MainMenu
	UFUNCTION()
		void QuitButtonPressed();

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* QuitButton;
};
