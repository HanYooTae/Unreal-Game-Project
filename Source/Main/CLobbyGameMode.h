#pragma once

#include "CoreMinimal.h"
#include "MainGameModeBase.h"
#include "CLobbyGameMode.generated.h"

UCLASS()
class MAIN_API ACLobbyGameMode : public AMainGameModeBase
{
	GENERATED_BODY()
	
public:
	void PostLogin(APlayerController* NewPlayer) override;
	void Logout(AController* Exiting) override;

private:
	void StartGame();

private:
	uint32 NumberOfPlayers;
};
