#include "Menu/CLose.h"
#include "Global.h"
#include "Components/Button.h"
#include "Instance_and_GameMode/CGameInstance.h"

bool UCLose::Initialize()
{
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	CheckNullResult(QuitButton, false);
	QuitButton->OnClicked.AddDynamic(this, &UCLose::QuitButtonPressed);

	return true;
}

void UCLose::QuitButtonPressed()
{
	Detach();

	UCGameInstance* gameInstance = Cast<UCGameInstance>(GetGameInstance());
	gameInstance->ReturnToMainMenu();
}
