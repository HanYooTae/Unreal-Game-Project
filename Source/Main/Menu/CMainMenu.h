#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu/CMenuBase.h"
#include "CMainMenu.generated.h"

UCLASS()
class MAIN_API UCMainMenu : public UCMenuBase
{
	GENERATED_BODY()
	
public:
	UCMainMenu(const FObjectInitializer& ObjectInitializer);

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION() void OpenMainMenu();
	UFUNCTION() void OpenJoinGameMenu();
	UFUNCTION() void OpenHostSessionMenu();
	UFUNCTION() void QuitGame();

private:	// Create & Join Session
	UFUNCTION()	void HostServer();

private:
	// Menu
	UPROPERTY(meta = (BindWidget))
		class UWidget* MainMenu;
	UPROPERTY(meta = (BindWidget))
		class UWidget* JoinGameMenu;
	UPROPERTY(meta = (BindWidget))
		class UWidget* HostSessionMenu;
		

	// MenuSwitcher
	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* MenuSwitcher;

	// MainMenu Button
	UPROPERTY(meta = (BindWidget))
		class UButton* MainMenuCreateButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* MainMenuJoinButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* QuitButton;

	// JoinGameMenu Button
	UPROPERTY(meta = (BindWidget))
		class UButton* JoinGameBackButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* JoinGameJoinButton;
	UPROPERTY(meta = (BindWidget))
		class UScrollBox* SessionList;

	// HostSessionMenu
	UPROPERTY(meta = (BindWidget))
		class UButton* HostSessionBackButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* HostSessionCreateButton;
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* SessionNameText;
};
