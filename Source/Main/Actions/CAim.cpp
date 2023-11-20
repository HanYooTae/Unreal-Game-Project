#include "Actions/CAim.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/cameraComponent.h"
#include "CHUD.h"

UCAim::UCAim()
{
}

void UCAim::BeginPlay(ACharacter* InOwnerCharacter)
{
	OwnerCharacter = InOwnerCharacter;

	SpringArm = Cast<USpringArmComponent>(OwnerCharacter->GetComponentByClass(USpringArmComponent::StaticClass()));

	Camera = Cast<UCameraComponent>(OwnerCharacter->GetComponentByClass(UCameraComponent::StaticClass()));

	UWorld* world = OwnerCharacter->GetWorld();

	HUD = world->GetFirstPlayerController()->GetHUD<ACHUD>();
}

void UCAim::Tick(float DeltaTime)
{
}

void UCAim::On()
{
	CheckFalse(IsAvailable());
	CheckTrue(bZooming);
	bZooming = true;

	HUD->EnableAim();

	SpringArm->TargetArmLength = 100.f;
	SpringArm->SocketOffset = FVector(0, 0, 40);
	SpringArm->bEnableCameraLag = false;
}

void UCAim::Off()
{
	CheckFalse(IsAvailable());
	CheckFalse(bZooming);
	bZooming = false;

	HUD->DisableAim();

	SpringArm->TargetArmLength = 200.f;
	SpringArm->SocketOffset = FVector::ZeroVector;
	SpringArm->bEnableCameraLag = true;
}