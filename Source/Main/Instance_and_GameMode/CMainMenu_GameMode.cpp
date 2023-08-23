#include "Instance_and_GameMode/CMainMenu_GameMode.h"
#include "Global.h"

ACMainMenu_GameMode::ACMainMenu_GameMode()
{
	CHelpers::GetClass(&DefaultPawnClass, "Blueprint'/Game/Character/TempPlayer.TempPlayer_C'");

	 
}