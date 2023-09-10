#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CInteractionWidget.generated.h"

UCLASS()
class MAIN_API UCInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Interaction")
		void UpdateInteractionWidget(class UCInteractionComponent* InteractionComponent);

	UFUNCTION(BlueprintImplementableEvent)
		void OnUpdateInteractionWidget();

	UPROPERTY(BlueprintReadOnly, Category = "Interaction", meta = (ExposeOnSpawn))
		class UCInteractionComponent* OwningInteractionComponent;



};
