#include "CPlayer/CPlayer.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"
#include "../ActorComponent/CParkourSystem.h"
#include "CAnimInstance.h"
#include "Widget/CMainWidget.h"
#include "Components/SceneCaptureComponent2D.h"
//#include "PaperSpriteComponent.h"

ACPlayer::ACPlayer()
{
	CHelpers::CreateActorComponent(this, &parkour, "ACParkour");
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	ConstructorHelpers::FObjectFinder<USkeletalMesh> meshAsset(TEXT("SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (meshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(meshAsset.Object);
	
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	ConstructorHelpers::FClassFinder<UCAnimInstance> animClass(TEXT("AnimBlueprint'/Game/Character/Animations/ABP_CPlayer.ABP_CPlayer_C'"));
	if (animClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(animClass.Class);

	//<SpringArm>
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 200.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetRelativeLocation(FVector(0, 0, 60));

	//Camera
	Camera->SetupAttachment(SpringArm);

	//Movement
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;

	// Minimap Setting
	MinimapSpringArm = CreateDefaultSubobject<USpringArmComponent>("MinimapSpringArm");
	RenderMinimap = CreateDefaultSubobject<USceneCaptureComponent2D>("RenderMinimap");
	RenderMinimap->SetupAttachment(MinimapSpringArm);
	//Arrow->SetupAttachment(RenderMinimap);		// PaperSpriteComponent Error!!

	// Render Minimap
	MinimapSpringArm->SetupAttachment(GetCapsuleComponent());
	MinimapSpringArm->TargetArmLength = 900.f;
	MinimapSpringArm->bUsePawnControlRotation = true;
	MinimapSpringArm->SetRelativeRotation(FRotator(-90, 0, 0));


	// Change Camera Settings
	MinimapSpringArm->bUsePawnControlRotation = false;
	MinimapSpringArm->bInheritPitch = false;
	MinimapSpringArm->bInheritYaw = false;
	MinimapSpringArm->bInheritRoll = false;

	// MainWidget
	CHelpers::GetClass(&MainWidgetClass, "WidgetBlueprint'/Game/Widget/WB_MainWidget.WB_MainWidget_C'");
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	//Get Material Asset
	UMaterialInstanceConstant* bodyMaterialAsset;
	CHelpers::GetAssetDynamic(&bodyMaterialAsset, "MaterialInstanceConstant'/Game/Character/Materials/M_UE4Man_Body_Inst.M_UE4Man_Body_Inst'");

	UMaterialInstanceConstant* logoMaterialAsset;
	CHelpers::GetAssetDynamic(&logoMaterialAsset, "MaterialInstanceConstant'/Game/Character/Materials/M_UE4Man_ChestLogo.M_UE4Man_ChestLogo'");

	//Create Dynamic Material
	BodyMaterial = UMaterialInstanceDynamic::Create(bodyMaterialAsset, nullptr);
	LogoMaterial = UMaterialInstanceDynamic::Create(logoMaterialAsset, nullptr);

	//Set Dynamic Material to Mesh Comp
	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	// Create & Attach MainWidget
	MainWidget = CreateWidget<UCMainWidget>(GetWorld(), MainWidgetClass);
	CheckNull(MainWidget);
	MainWidget->AddToViewport();
	//MainWidget->RemoveFromParent();

	// Hidden Players in Minimap
	CheckNull(RenderMinimap);
	RenderMinimap->ShowFlags.SkeletalMeshes = false;
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Axis Event
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);

	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);
	
	
	//Action Event
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACPlayer::OnSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACPlayer::OffSprint);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACPlayer::StartJump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ACPlayer::StopJump);
	PlayerInputComponent->BindAction("Vaulting", EInputEvent::IE_Pressed, parkour, &UCParkourSystem::Vault);

}

void ACPlayer::OnMoveForward(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnHorizontalLook(float Axis)
{
	AddControllerYawInput(Axis);
}

void ACPlayer::OnVerticalLook(float Axis)
{
	AddControllerPitchInput(Axis);
}

void ACPlayer::OnSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ACPlayer::OffSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void ACPlayer::StartJump()
{
	bPressedJump = true;
}

void ACPlayer::StopJump()
{
	bPressedJump = false;
}

void ACPlayer::SetMainWidget()
{

}



