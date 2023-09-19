#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystem.h"
#include "Menu/CMainMenu.h"
#include "CGameInstance.generated.h"

UCLASS()
class MAIN_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

public:
	UFUNCTION(BlueprintCallable)
		void LoadMenu();		// Menu Init
	
	UFUNCTION()
		void Host(const FString& InSessionName);		// Enter to Server(Create Session & Destroy Session)

	virtual void ReturnToMainMenu() override;

public:	// Session Event
	void CreateSession();
	void FindSession();

private:	// Session Delegate
	void OnCreateSessionComplete(FName InSessionName, bool InSuccess);
	void OnDestroySessionComplete(FName InSessionName, bool InSuccess);
	void OnFindSessionsComplete(bool InSccess);

private:
	TSubclassOf<UCMainMenu> MainMenuClass;
	UCMainMenu* MainMenu;

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SearchSettings;

	FString SessionName;
};