#include "Widget/CSelectActionWidget_Icon.h"
#include "CSelectActionWidget_Group.h"
#include "Global.h"
#include "Components/Button.h"
#include "CPlayer/CPlayer.h"
#include "Engine/Texture2D.h"

void UCSelectActionWidget_Icon::NativeConstruct()
{
	Super::NativeConstruct();

	CheckNull(ImageButton);
	ImageButton->OnPressed.AddDynamic(this, &UCSelectActionWidget_Icon::OnPressed);
	ImageButton->OnHovered.AddDynamic(this, &UCSelectActionWidget_Icon::OnHover);
	ImageButton->OnUnhovered.AddDynamic(this, &UCSelectActionWidget_Icon::OnUnhover);
}

void UCSelectActionWidget_Icon::OnPressed()
{
	CheckNull(GetParentWidget());
	GetParentWidget()->Pressed(GetName());
}

void UCSelectActionWidget_Icon::OnHover()
{
	CheckNull(GetParentWidget());
	GetParentWidget()->Hover(GetName());
}

void UCSelectActionWidget_Icon::OnUnhover()
{
	CheckNull(GetParentWidget());
	GetParentWidget()->Unhover(GetName());
}

void UCSelectActionWidget_Icon::SetTextureImageButton(UTexture2D* InImage)
{
	CheckNull(ImageButton);
	ImageButton->WidgetStyle.Normal.SetResourceObject(InImage);
	ImageButton->WidgetStyle.Hovered.SetResourceObject(InImage);
	ImageButton->WidgetStyle.Pressed.SetResourceObject(InImage);
}

UCSelectActionWidget_Group* UCSelectActionWidget_Icon::GetParentWidget()
{
	ACPlayer* player = Cast<ACPlayer>(GetOwningPlayer()->GetCharacter());
	CheckNullResult(player, nullptr);

	return player->GetSelectActionWidget();
}