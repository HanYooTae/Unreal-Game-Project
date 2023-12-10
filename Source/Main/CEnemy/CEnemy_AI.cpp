#include "CEnemy/CEnemy_AI.h"
#include "Global.h"
#include "CharacterComponents/CPatrolComponent.h"

ACEnemy_AI::ACEnemy_AI()
{
	CHelpers::CreateActorComponent(this, &Patrol, "Patrol");
}