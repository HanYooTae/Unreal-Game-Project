#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CharacterComponents/CStatusComponent.h"
#include "CBTTaskNode_MoveSpeed.generated.h"

UCLASS()
class MAIN_API UCBTTaskNode_MoveSpeed : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UCBTTaskNode_MoveSpeed();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere)
		EWalkSpeedType Type;

};
