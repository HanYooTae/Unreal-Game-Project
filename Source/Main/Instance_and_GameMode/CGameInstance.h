#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystem.h"
#include "Menu/CMainMenu.h"
#include "Menu/CBackQuitMenu.h"
#include "CGameInstance.generated.h"

UCLASS()
class MAIN_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

public:	// Button Pressed
	void Host(const FString& InSessionName);

public:	// OSS
	void CreateSession();

public:	// OSS_Delegate
	void OnCreateSessionComplete(FName SessionName, bool bSuccess);
	void OnDestroySessionComplete(FName SessionName, bool bSuccess);

public:	// Menu Init
	UFUNCTION(BlueprintCallable)
		void LoadMainMenu();

	UFUNCTION(BlueprintCallable)
		void LoadBackQuitMenu();

public:	// Menu Function
	// LoadBackQuitMenu -> QuitButton
	void ReturnToMainMenu();


	FString Current_SessionName;
private:
	TSubclassOf<UCMainMenu> MainMenuClass;
	TSubclassOf<UCBackQuitMenu> BackQuitMenuClass;

	UCMainMenu* MainMenu;
	UCBackQuitMenu* BackQuitMenu;

	IOnlineSessionPtr SessionInterface;

};