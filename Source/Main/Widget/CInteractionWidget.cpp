#include "Widget/CInteractionWidget.h"
#include "Global.h"
#include "../ActorComponent/CInteractionComponent.h"

void UCInteractionWidget::UpdateInteractionWidget(class UCInteractionComponent* InteractionComponent)
{
	OwningInteractionComponent = InteractionComponent;
	OnUpdateInteractionWidget();
}

