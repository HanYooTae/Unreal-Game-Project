#include "Menu/CClear.h"
#include "Global.h"
#include "Components/Button.h"
#include "Instance_and_GameMode/CGameInstance.h"

bool UCClear::Initialize()
{
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	CheckNullResult(QuitButton, false);
	QuitButton->OnClicked.AddDynamic(this, &UCClear::QuitButtonPressed);

	return true;
}

void UCClear::QuitButtonPressed()
{
	Detach();

	UCGameInstance* gameInstance = Cast<UCGameInstance>(GetGameInstance());
	gameInstance->ReturnToMainMenu();
}
