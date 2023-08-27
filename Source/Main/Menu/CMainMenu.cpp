#include "Menu/CMainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Global.h"

bool UCMainMenu::Initialize()
{
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);
	
	// MainMenu Button
	CheckNullResult(MainMenuCreateButton, false);
	MainMenuCreateButton->OnClicked.AddDynamic(this, &UCMainMenu::OpenHostSessionMenu);
	CheckNullResult(MainMenuJoinButton, false);
	MainMenuJoinButton->OnClicked.AddDynamic(this, &UCMainMenu::OpenJoinGameMenu);
	CheckNullResult(QuitButton, false);
	QuitButton->OnClicked.AddDynamic(this, &UCMainMenu::QuitGame);

	// JoinGameMenu Button
	CheckNullResult(JoinGameBackButton, false);
	JoinGameBackButton->OnClicked.AddDynamic(this, &UCMainMenu::OpenMainMenu);

	// HostSessionMenu
	CheckNullResult(HostSessionBackButton, false);
	HostSessionBackButton->OnClicked.AddDynamic(this, &UCMainMenu::OpenMainMenu);

	return true;
}

void UCMainMenu::OpenMainMenu()
{
	CheckNull(MenuSwitcher);
	CheckNull(MainMenu);
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UCMainMenu::OpenJoinGameMenu()
{
	CheckNull(MenuSwitcher);
	CheckNull(JoinGameMenu);
	MenuSwitcher->SetActiveWidget(JoinGameMenu);
}

void UCMainMenu::OpenHostSessionMenu()
{
	CheckNull(MenuSwitcher);
	CheckNull(HostSessionMenu);
	MenuSwitcher->SetActiveWidget(HostSessionMenu);
}

void UCMainMenu::QuitGame()
{
	UWorld* world = GetWorld();
	CheckNull(world);

	APlayerController* controller = world->GetFirstPlayerController();

	controller->ConsoleCommand("Quit");
}