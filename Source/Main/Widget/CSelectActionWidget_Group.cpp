#include "Widget/CSelectActionWidget_Group.h"
#include "Global.h"
#include "Components/GridPanel.h"
#include "Components/Border.h"
#include "CSelectActionWidget_Icon.h"

void UCSelectActionWidget_Group::NativeConstruct()
{
	Super::NativeConstruct();

	// Icon1, Icon2, Icon3ÀÇ ¹­À½
	CheckNull(Grid);
	TArray<UWidget*> children = Grid->GetAllChildren();

	for (const auto& child : children)
	{
		UCSelectActionWidget_Icon* iconWidget = Cast<UCSelectActionWidget_Icon>(child);

		if (!!iconWidget)
			IconWidgets.Add(child->GetName(), iconWidget);
	}

	// Set Images to IconWidget ImageButton
	for (int32 i = 0; i < IconWidgets.Num(); i++)
	{
		FString key = "Icon";
		key.Append(FString::FromInt(i + 1));

		IconWidgets[key]->SetTextureImageButton(Images[i]);
	}
}

void UCSelectActionWidget_Group::Pressed(FString InKey)
{
	if (IconWidgets[InKey]->OnImageButtonPressed.IsBound())
		IconWidgets[InKey]->OnImageButtonPressed.Broadcast();

	SetVisibility(ESlateVisibility::Hidden);
	APlayerController* controller = Cast<APlayerController>(GetOwningPlayer());
	CheckNull(controller);

	controller->bShowMouseCursor = false;
	controller->SetInputMode(FInputModeGameOnly());
}

void UCSelectActionWidget_Group::Hover(FString InKey)
{
	// BorderColor => Red
	UBorder* border = Cast<UBorder>(IconWidgets[InKey]->GetWidgetFromName("MyBorder"));
	CheckNull(border);
	border->SetBrushColor(FLinearColor::Red);
}

void UCSelectActionWidget_Group::Unhover(FString InKey)
{
	// BorderColor => White
	UBorder* border = Cast<UBorder>(IconWidgets[InKey]->GetWidgetFromName("MyBorder"));
	CheckNull(border);
	border->SetBrushColor(FLinearColor::White);
}