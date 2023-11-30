#include "BehaviorTree/CEnvQueryContext_Player.h"
#include "Global.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "CEnemy/CEnemy_AI.h"
#include "CEnemy/CAIController.h"
#include "CPlayer/CPlayer.h"
#include "CharacterComponents/CBehaviorComponent.h"

void UCEnvQueryContext_Player::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	//적을 가져오면 -> 컨트롤러 -> BehaviorComp::GetPlayerKey
	ACEnemy_AI* enemy = Cast<ACEnemy_AI>(QueryInstance.Owner.Get());
	CheckNull(enemy);

	ACAIController* controller = Cast<ACAIController>(enemy->GetController());
	CheckNull(controller);

	UCBehaviorComponent* behaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	CheckNull(behaviorComp);

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, behaviorComp->GetPlayerKey());
}