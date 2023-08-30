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

private:
	TSubclassOf<UCMainMenu> MainMenuClass;

	UCMainMenu* MainMenu;
};