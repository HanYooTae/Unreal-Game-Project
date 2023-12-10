#include "CLobbyGameMode.h"
#include "Global.h"
#include "Instance_and_GameMode/CGameInstance.h"

void ACLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	NumberOfPlayers++;
	CLog::Print("Player : " + FString::FromInt(NumberOfPlayers));

	if (NumberOfPlayers >= 2)
	{
		CLog::Print("Ready to play");

		FTimerHandle timerHandle;
		GetWorldTimerManager().SetTimer(timerHandle, this, &ACLobbyGameMode::StartGame, 5);
	}
}

void ACLobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	NumberOfPlayers--;
	CLog::Print("Player : " + FString::FromInt(NumberOfPlayers));
}

void ACLobbyGameMode::StartGame()
{
	UCGameInstance* gameInstance = Cast<UCGameInstance>(GetGameInstance());
	CheckNull(gameInstance);
	gameInstance->StartSession();

	UWorld* world = GetWorld();
	CheckNull(world);

	bUseSeamlessTravel = true;
	world->ServerTravel("/Game/Map/Main1?listen'");
}