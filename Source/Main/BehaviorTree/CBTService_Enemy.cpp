#include "BehaviorTree/CBTService_Enemy.h"
#include "Global.h"
#include "CharacterComponents/CBehaviorComponent.h"
#include "CharacterComponents/CStateComponent.h"
#include "CharacterComponents/CPatrolComponent.h"
#include "CEnemy/CAIController.h"
#include "CEnemy/CEnemy_AI.h"
#include "CPlayer/CPlayer.h"

UCBTService_Enemy::UCBTService_Enemy()
{
	NodeName = "Enemy";
}

void UCBTService_Enemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	CheckNull(controller);

	UCBehaviorComponent* behaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	CheckNull(behaviorComp);

	ACEnemy_AI* enemy = Cast<ACEnemy_AI>(controller->GetPawn());
	CheckNull(enemy);

	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(enemy);
	CheckNull(stateComp);

	UCPatrolComponent* patrolComp = CHelpers::GetComponent<UCPatrolComponent>(enemy);
	CheckNull(patrolComp);

	//Hitted
	if (stateComp->IsHittedMode())
	{
		behaviorComp->SetHittedMode();
		return;
	}

	//Get Player from BB
	ACPlayer* player = behaviorComp->GetPlayerKey();

	//No Perceived Player
	if (player == nullptr)
	{
		if (patrolComp->IsPathValid())
		{
			behaviorComp->SetPatrolMode();
			return;
		}

		behaviorComp->SetWaitMode();
		return;
	}

	//Perceived Player
	UCStateComponent* playerStateComp = CHelpers::GetComponent<UCStateComponent>(player);
	if (!!playerStateComp)
	{
		if (playerStateComp->IsDeadMode())
		{
			behaviorComp->SetWaitMode();
			return;
		}
	}

	//-> Get Distance to Player
	float distance = enemy->GetDistanceTo(player);

	//-> Is in Attack Range
	if (distance < controller->GetBehaviorRange())
	{
		behaviorComp->SetActionMode();
		return;
	}

	//-> Is in Sight Range
	if (distance < controller->GetSightRadius())
	{
		behaviorComp->SetApproachMode();
		return;
	}

}
