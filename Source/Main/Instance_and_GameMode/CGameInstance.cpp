#include "Instance_and_GameMode/CGameInstance.h"
#include "Global.h"

UCGameInstance::UCGameInstance(const FObjectInitializer& ObjectInitializer)
{
	CHelpers::GetClass(&MainMenuClass, "WidgetBlueprint'/Game/Widget/Menu/WB_MainMenu.WB_MainMenu_C'");
}

void UCGameInstance::Init()
{
	Super::Init();
	CLog::Print("GameInstace::Constructor Called");


}

void UCGameInstance::LoadMenu()
{
	CheckNull(MainMenuClass);
	MainMenu = CreateWidget<UCMainMenu>(this, MainMenuClass);
	CheckNull(MainMenu);

	MainMenu->Attach();
}
