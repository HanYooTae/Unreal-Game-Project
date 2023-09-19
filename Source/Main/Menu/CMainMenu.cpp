#include "Menu/CMainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Global.h"
#include "Instance_and_GameMode/CGameInstance.h"
#include "CSessionRow.h"

UCMainMenu::UCMainMenu(const FObjectInitializer& ObjectInitializer)
{
	CHelpers::GetClass(&SessionRowClass, "WidgetBlueprint'/Game/Widget/Menu/WB_SessionRow.WB_SessionRow_C'");
}

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
	CheckNullResult(JoinGameJoinButton, false);
	JoinGameJoinButton->OnClicked.AddDynamic(this, &UCMainMenu::JoinServer);

	// HostSessionMenu
	CheckNullResult(HostSessionBackButton, false);
	HostSessionBackButton->OnClicked.AddDynamic(this, &UCMainMenu::OpenMainMenu);
	CheckNullResult(HostSessionCreateButton, false);
	HostSessionCreateButton->OnClicked.AddDynamic(this, &UCMainMenu::HostServer);

	return true;
}

void UCMainMenu::SetSessionList(TArray<FSessionData> InSessionDatas)
{
	UWorld* world = GetWorld();
	CheckNull(world);

	SessionList->ClearChildren();

	uint32 i = 0;
	for (const auto& data : InSessionDatas)
	{
		UCSessionRow* sessionRow = CreateWidget<UCSessionRow>(world, SessionRowClass);
		CheckNull(sessionRow);

		sessionRow->SessionName->SetText(FText::FromString(data.SessionName));
		sessionRow->HostUserName->SetText(FText::FromString(data.HostUserName));

		FString fractionStr = FString::Printf(L"%d/%d", data.CurrentPlayers, data.MaxPlayers);
		sessionRow->ConnectionFractions->SetText(FText::FromString(fractionStr));

		sessionRow->SetSelfIndex(this, i++);

		SessionList->AddChild(sessionRow);
	}
}

void UCMainMenu::SetSelectedRowIndex(uint32 InIndex)
{
	SelectedRowIndex = InIndex;
}

void UCMainMenu::SelectedSessionRow()
{
	for (int32 i = 0; i < SessionList->GetChildrenCount(); i++)
	{
		UCSessionRow* sessionRow = Cast<UCSessionRow>(SessionList->GetChildAt(i));

		if (!!sessionRow)	// If Clicked, IsSet change false to true && Only Clicked Index change color itself.
			sessionRow->bSelfClicked = (SelectedRowIndex.IsSet() && i == SelectedRowIndex);
	}
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

	UCGameInstance* gameInstance = Cast<UCGameInstance>(GetGameInstance());
	CheckNull(gameInstance);

	gameInstance->FindSession();
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

void UCMainMenu::HostServer()
{
	FString sessionName = SessionNameText->GetText().ToString();

	UCGameInstance* gameInstance = Cast<UCGameInstance>(GetGameInstance());
	CheckNull(gameInstance);

	gameInstance->Host(sessionName);

	CLog::Log("Host Button Pressed");
}