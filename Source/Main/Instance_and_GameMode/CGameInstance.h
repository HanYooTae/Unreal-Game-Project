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

public:	// Menu Init
	UFUNCTION(BlueprintCallable)
		void LoadMenu();

	UFUNCTION()
		void Host(const FString& InSessionName);

	virtual void ReturnToMainMenu() override;

private:
	void CreateSession();

private:	// Session Delegate
	void OnCreateSessionComplete(FName InSessionName, bool InSuccess);
	void OnDestroySessionComplete(FName InSessionName, bool InSuccess);

private:
	TSubclassOf<UCMainMenu> MainMenuClass;
	UCMainMenu* MainMenu;

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	FString DesiredSessionName;
};