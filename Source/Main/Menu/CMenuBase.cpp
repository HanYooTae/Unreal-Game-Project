#include "Menu/CMenuBase.h"
#include "Global.h"

void UCMenuBase::Attach()
{
	AddToViewport();

	bIsFocusable = true;

	FInputModeUIOnly inputMode;
	inputMode.SetWidgetToFocus(TakeWidget());
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	UWorld* world = GetWorld();
	CheckNull(world);
	APlayerController* controller = world->GetFirstPlayerController();
	CheckNull(controller);

	controller->SetInputMode(inputMode);
	controller->bShowMouseCursor = true;
}

void UCMenuBase::Detach()
{
}
