#include "CHUD.h"
#include "Engine/Canvas.h"
#include "Global.h"
#include "CharacterComponents/CStateComponent.h"
#include "GameFramework/Character.h"

ACHUD::ACHUD()
{
	CHelpers::GetAsset<UTexture2D>(&CrosshairTex, "Texture2D'/Game/Assets/Textures/FirstPersonCrosshair.FirstPersonCrosshair'");
}

void ACHUD::BeginPlay()
{
	Super::BeginPlay();

	// playerCharacter->ActionComp->Type => FString => print
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	CheckNull(playerCharacter);

	StateComp = CHelpers::GetComponent<UCStateComponent>(playerCharacter);

	StateTypeEnum = FindObject<UEnum>(ANY_PACKAGE, L"EStateType", true);
}

void ACHUD::DrawHUD()
{
	Super::DrawHUD();

	// Print Player StateType
	CheckNull(StateComp);
	CheckNull(StateTypeEnum);

	FString typeStr = StateTypeEnum->GetNameStringByValue((int64)StateComp->GetType());

	DrawText(typeStr, FLinearColor::Red, 10, Canvas->ClipY - 50, nullptr, 1.5f);

	// Draw Aim
	CheckFalse(bVisibleAim);

	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	const FVector2D CrosshairDrawPosition((Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5)),
		(Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)));

	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}