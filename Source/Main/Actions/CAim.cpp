#include "Actions/CAim.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/cameraComponent.h"
#include "CHUD.h"

UCAim::UCAim()
{
	CHelpers::GetAsset<UCurveFloat>(&Curve, "CurveFloat'/Game/Assets/Assets/Curve_Aim.Curve_Aim'");
}

void UCAim::BeginPlay(ACharacter* InOwnerCharacter)
{
	OwnerCharacter = InOwnerCharacter;

	SpringArm = Cast<USpringArmComponent>(OwnerCharacter->GetComponentByClass(USpringArmComponent::StaticClass()));
	Camera = Cast<UCameraComponent>(OwnerCharacter->GetComponentByClass(UCameraComponent::StaticClass()));

	OnTimeline.BindUFunction(this, "Zooming");
	Timeline.AddInterpFloat(Curve, OnTimeline);
	Timeline.SetPlayRate(5.f);

	UWorld* world = OwnerCharacter->GetWorld();

	HUD = world->GetFirstPlayerController()->GetHUD<ACHUD>();
}

void UCAim::Tick(float DeltaTime)
{
	Timeline.TickTimeline(DeltaTime);
}

void UCAim::On_Implementation()
{
	CheckFalse(IsAvailable());
	CheckTrue(bZooming);
	bZooming = true;

	HUD->EnableAim();

	SpringArm->TargetArmLength = 100.f;
	SpringArm->SocketOffset = FVector(0, 50, 10);
	SpringArm->bEnableCameraLag = false;

	//Camera->FieldOfView = 45.f;
	Timeline.PlayFromStart();
}

void UCAim::Off_Implementation()
{
	CheckFalse(IsAvailable());
	CheckFalse(bZooming);
	bZooming = false;

	HUD->DisableAim();

	SpringArm->TargetArmLength = 200.f;
	SpringArm->SocketOffset = FVector::ZeroVector;
	SpringArm->bEnableCameraLag = true;

	//Camera->FieldOfView = 90.f;
	Timeline.ReverseFromEnd();
}

void UCAim::Zooming(float Output)
{
	Camera->FieldOfView = Output;
}
