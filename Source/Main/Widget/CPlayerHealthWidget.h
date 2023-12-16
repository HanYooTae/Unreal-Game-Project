#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPlayerHealthWidget.generated.h"

UCLASS()
class MAIN_API UCPlayerHealthWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintNativeEvent)
		void UpdateHealth();
	void UpdateHealth_Implementation();

	UFUNCTION(Client, Reliable)
		void UpdateHealth_Client();
	void UpdateHealth_Client_Implementation();

private:
	UPROPERTY(meta = (BindWidget))
		class UImage* CircleGuage;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CurrentHealthText;

	/*UPROPERTY(meta = (BindWidgetAnimation))
		class UWidgetAnimation* ImpactDamage;*/

private:
	class UMaterialInstanceDynamic* Material;
	class UCStatusComponent* StatusComp;
	FString CurrentHealthStr;
};
