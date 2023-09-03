#include "MainGameModeBase.h"
#include "CPlayer/CPlayer.h"

AMainGameModeBase::AMainGameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn> pawnAsset(TEXT("Blueprint'/Game/Character/MyCPlayer.MyCPlayer_C'"));

	if (pawnAsset.Succeeded())
		DefaultPawnClass = pawnAsset.Class;

}