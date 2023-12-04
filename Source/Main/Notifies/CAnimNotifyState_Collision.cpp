#include "Notifies/CAnimNotifyState_Collision.h"
#include "Notifies/CAnimNotifyState_Collision.h"
#include "Global.h"
#include "CharacterComponents/CActionComponent.h"
#include "Actions/CWeapon.h"
#include "Actions/CActionData_Spawned.h"
#include "Actions/CDoAction_Melee.h"

FString	UCAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* actionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComp);

	UCActionData_Spawned* currentData = actionComp->GetCurrentData();
	CheckNull(currentData);

	ACWeapon* weapon = currentData->GetWeapon();
	CheckNull(weapon);

	weapon->OnCollisions();
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* actionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComp);

	UCActionData_Spawned* currentData = actionComp->GetCurrentData();
	CheckNull(currentData);

	ACWeapon* weapon = currentData->GetWeapon();
	CheckNull(weapon);

	weapon->OffCollisions();

	ACDoAction_Melee* doAction_melee = Cast<ACDoAction_Melee>(currentData->GetDoAction());
	CheckNull(doAction_melee);
	
	// 다단히트 방지
	doAction_melee->ClearHittedCharacters();
}