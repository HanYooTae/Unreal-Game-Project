#include "ActorComponent/CTimeDilationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Global.h"

UCTimeDilationSystem::UCTimeDilationSystem()
{

}


void UCTimeDilationSystem::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	CheckNull(world);
	// Change speed what you want
	GetWorld()->GetWorldSettings()->CustomTimeDilation = Adjust_Time;
}