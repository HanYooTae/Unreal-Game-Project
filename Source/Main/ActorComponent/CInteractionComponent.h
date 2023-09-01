#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "CInteractionComponent.generated.h"

UCLASS(ClassGroup = "Custom", meta = (BlueprintSpawnableComponent))
class MAIN_API UCInteractionComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

	UCInteractionComponent();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Interaction")
		float InteractionTime;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Interaction")
		float InteractionDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Interaction")
		FText InteractableNameText;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Interaction")
		FText InteractableActionText;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Interaction")
		bool bAllowMultipleInteractors;
			
};
