#include "Widget/CPlayerHealthWidget.h"
#include "Global.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "CPlayer/CPlayer.h"
#include "CharacterComponents/CStatusComponent.h"
#include "Animation/WidgetAnimation.h"

void UCPlayerHealthWidget::NativeConstruct()
{
	CheckNull(CircleGuage);
	Material = CircleGuage->GetDynamicMaterial();
	CheckNull(Material);

	ACPlayer* player = Cast<ACPlayer>(GetOwningPlayer()->GetCharacter());
	CheckNull(player);

	StatusComp = CHelpers::GetComponent<UCStatusComponent>(player);
	CheckNull(StatusComp);

	Material->SetScalarParameterValue("Ratio", StatusComp->GetCurrentHealth() / StatusComp->GetMaxHealth());

	CheckNull(CurrentHealthText);
	CurrentHealthStr = FString::FromInt((int32)StatusComp->GetCurrentHealth());
	CurrentHealthText->SetText(FText::FromString(CurrentHealthStr));

	Super::NativeConstruct();
}

void UCPlayerHealthWidget::UpdateHealth_Implementation()
{
	CheckNull(Material);
	CheckNull(StatusComp);

	Material->SetScalarParameterValue("Ratio", StatusComp->GetCurrentHealth() / StatusComp->GetMaxHealth());

	CheckNull(CurrentHealthText);
	CurrentHealthStr = FString::FromInt((int32)StatusComp->GetCurrentHealth());
	CurrentHealthText->SetText(FText::FromString(CurrentHealthStr));

	//PlayAnimation(ImpactDamage);
}