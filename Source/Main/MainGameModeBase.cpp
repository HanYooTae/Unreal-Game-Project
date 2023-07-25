#include "MainGameModeBase.h"
#include "CPlayer/CPlayer.h"

AMainGameModeBase::AMainGameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn> pawnAsset(TEXT("Blueprint'/Game/Character/BP_CPlayer.BP_CPlayer_C'"));

	if (pawnAsset.Succeeded())
		DefaultPawnClass = pawnAsset.Class;
}


