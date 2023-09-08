#include "Menu/CBackQuitMenu.h"
#include "Global.h"
#include "Components/Button.h"
#include "Instance_And_GameMode/CGameInstance.h"

bool UCBackQuitMenu::Initialize()
{
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	CheckNullResult(BackButton, false);
	BackButton->OnClicked.AddDynamic(this, &UCBackQuitMenu::BackButtonPressed);
	CheckNullResult(QuitButton, false);
	QuitButton->OnClicked.AddDynamic(this, &UCBackQuitMenu::QuitButtonPressed);

	return true;
}


void UCBackQuitMenu::BackButtonPressed()
{
	Detach();
}


void UCBackQuitMenu::QuitButtonPressed()
{
	Detach();

	UCGameInstance* gameInstance = Cast<UCGameInstance>(GetGameInstance());
	CheckNull(gameInstance);

	gameInstance->ReturnToMainMenu();
}
