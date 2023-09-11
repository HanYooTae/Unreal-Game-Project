#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSessionRow.generated.h"

UCLASS()
class MAIN_API UCSessionRow : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetSelfIndex(class UCMenu* InParent, uint32 InIndex);

	UFUNCTION() void OnClick();

private:
	// SessionList Button
	UPROPERTY(meta = (BindWidget))
		class UButton* RowButton;

	// RowButton Composition
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SessionName;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* HostUserName;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ConnectionFractions;

	class UCMenu* Parent;
	uint32 Index;
};
