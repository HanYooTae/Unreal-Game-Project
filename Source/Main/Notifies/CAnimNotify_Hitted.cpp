#include "Notifies/CAnimNotify_Hitted.h"
#include "Global.h"
#include "CharacterComponents/CStateComponent.h"

FString UCAnimNotify_Hitted::GetNotifyName_Implementation() const
{
	return "Hitted";
}

void UCAnimNotify_Hitted::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(Animation);

	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(MeshComp->GetOwner());
	CheckNull(stateComp);
	stateComp->SetIdleMode();
}