#include "ActorComponent/CInteractionComponent.h"

UCInteractionComponent::UCInteractionComponent()
{
	SetComponentTickEnabled(false);

	InteractionTime = 0.f;
	InteractionDistance = 200.f;
	InteractableNameText = FText::FromString("Interactable Object");
	InteractableActionText = FText::FromString("Interact");
	bAllowMultipleInteractors = true;

	Space = EWidgetSpace::Screen;
	DrawSize = FIntPoint(400, 100);
	bDrawAtDesiredSize = true;
	SetActive(true);
	SetHiddenInGame(true);
}

void UCInteractionComponent::BeginFocus(ACPlayer* Character)
{
	if (!IsActive() || !GetOwner() || !Character)
	{
		return;
	}

	OnBeginFocus.Broadcast(Character);

	SetHiddenInGame(false);

	if (!GetOwner()->HasAuthority())
	{

		for (auto& VisualComp : GetOwner()->GetComponentsByClass(UPrimitiveComponent::StaticClass()))
		{
			if (UPrimitiveComponent* prim = Cast<UPrimitiveComponent>(VisualComp))
			{
				prim->SetRenderCustomDepth(true);
			}
		}
	}

}

void UCInteractionComponent::EndFocus(ACPlayer* Character)
{
}

void UCInteractionComponent::BeginInteract(ACPlayer* Character)
{
}

void UCInteractionComponent::EndInteract(ACPlayer* Character)
{
}

void UCInteractionComponent::Interact(ACPlayer* Character)
{
	OnInteract.Broadcast(Character);
}
