#include "ActorComponent/CInteractionComponent.h"
#include "Global.h"
#include "../CPlayer/CPlayer.h"
#include "../Widget/CInteractionWidget.h"

UCInteractionComponent::UCInteractionComponent()
{
	SetComponentTickEnabled(false);

	InteractionTime = 0.f;
	InteractionDistance = 350.f;
	InteractableNameText = FText::FromString("Interactable Object");
	InteractableActionText = FText::FromString("Interact");
	bAllowMultipleInteractors = true;

	Space = EWidgetSpace::Screen;
	DrawSize = FIntPoint(600, 100);
	bDrawAtDesiredSize = true;
	SetActive(true);
	SetHiddenInGame(true);

	SetIsReplicated(true); //Todo.
}

void UCInteractionComponent::SetInteractableNameText(const FText& NewNameText)
{
	InteractableNameText = NewNameText;
	RefreshWidget();
}

void UCInteractionComponent::SetInteractableActionText(const FText& NewActionText)
{
	InteractableActionText = NewActionText;
	RefreshWidget();
}

void UCInteractionComponent::Deactivate()
{
	Super::Deactivate();

	for (int32 i = Interactors.Num() - 1; i >= 0; --i)
	{
		if (ACPlayer* Interactor = Interactors[i])
		{
			EndFocus(Interactor);
			EndInteract(Interactor);
		}
	}

	Interactors.Empty();
}

bool UCInteractionComponent::CanInteract(ACPlayer* Character) const
{
	const bool bPlayerAlreadyInteracting = !bAllowMultipleInteractors && Interactors.Num() >= 1;
	return !bPlayerAlreadyInteracting && IsActive() && GetOwner() != nullptr && Character != nullptr;
}

void UCInteractionComponent::RefreshWidget_Implementation()
{
	if (!bHiddenInGame && GetOwner()->GetNetMode() != NM_DedicatedServer/*전용 서버: 로컬 플레이어가 없는 서버입니다.*/)
	{
		if (UCInteractionWidget* InteractionWidget = Cast<UCInteractionWidget>(GetUserWidgetObject()))
		{
			InteractionWidget->UpdateInteractionWidget(this);
		}
	}
}

void UCInteractionComponent::BeginFocus(ACPlayer* Character)
{
	CLog::Print("1"); //Todo.
	if (!IsActive() || !GetOwner() || !Character)
	{
		return;
	}
	CLog::Print("2"); //Todo.

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

	RefreshWidget();
}

void UCInteractionComponent::EndFocus(ACPlayer* Character)
{
	OnEndFocus.Broadcast(Character);

	SetHiddenInGame(true);

	if (!GetOwner()->HasAuthority())
	{

		for (auto& VisualComp : GetOwner()->GetComponentsByClass(UPrimitiveComponent::StaticClass()))
		{
			if (UPrimitiveComponent* prim = Cast<UPrimitiveComponent>(VisualComp))
			{
				prim->SetRenderCustomDepth(false);
			}
		}
	}
}

void UCInteractionComponent::BeginInteract(ACPlayer* Character)
{
	if (CanInteract(Character))
	{
		Interactors.AddUnique(Character);
		OnBeginInteract.Broadcast(Character);
	}

}

void UCInteractionComponent::EndInteract(ACPlayer* Character)
{
	Interactors.RemoveSingle(Character);
	OnEndInteract.Broadcast(Character);
}

void UCInteractionComponent::Interact(ACPlayer* Character)
{
	if(CanInteract(Character))
		OnInteract.Broadcast(Character);
}

float UCInteractionComponent::GetInteractPercentage()
{
	if (Interactors.IsValidIndex(0))
	{
		if (ACPlayer* Interactor = Interactors[0])
		{
			if (Interactor && Interactor->IsInteracting())
			{
				return 1.f - FMath::Abs(Interactor->GetRemainingInteractime() / InteractionTime);
			}
		}
	}
	return 0.f;
}
