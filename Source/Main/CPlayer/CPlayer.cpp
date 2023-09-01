#include "CPlayer/CPlayer.h"
#include "Global.h"
#include "CAnimInstance.h"
#include "../Items/CItem.h"
#include "Widget/CMainWidget.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Items/CInventoryComponent.h"
#include "../ActorComponent/CParkourSystem.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"
#include "ActorComponent/CInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

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

	//Cameera
	Camera->SetupAttachment(SpringArm);

	Inventory = CreateDefaultSubobject<UCInventoryComponent>("Inventory");
	Inventory->Capacity = 20.f;

	//Movement
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;

	// MainWidget
	CHelpers::GetClass(&MainWidgetClass, "WidgetBlueprint'/Game/Widget/WB_MainWidget.WB_MainWidget_C'");

	Health = 100.0f; //test용 체력

	InteractionCheckFrequency = 0.f;
	InteractionCheckDistance = 1000.f;
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

	MainWidget = CreateWidget<UCMainWidget>(GetWorld(), MainWidgetClass);
	CheckNull(MainWidget);
	MainWidget->AddToViewport();
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PerformInteractionCheck();

}

void ACPlayer::PerformInteractionCheck()
{
	CheckNull(GetController());

	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	FVector EyesLoc;
	FRotator EyesRot;

	GetController()->GetPlayerViewPoint(EyesLoc, EyesRot);

	FVector TraceStart = EyesLoc;
	FVector TraceEnd = (EyesRot.Vector() * InteractionCheckDistance) + TraceStart;
	FHitResult TraceHit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		// 상호작용가능한 object를 Check
		if (TraceHit.GetActor())
		{
			if (UCInteractionComponent* InteractionComponent = Cast<UCInteractionComponent>(TraceHit.GetActor()->GetComponentByClass(UCInteractionComponent::StaticClass())))
			{
				float Distance = (TraceStart - TraceHit.ImpactPoint).Size();

				if (InteractionComponent != GetInteractable() && Distance <= InteractionComponent->InteractionDistance)
				{
					FoundNewInteractable(InteractionComponent);
				}
				else if (Distance > InteractionComponent->InteractionDistance && GetInteractable())
				{
					CouldnotFindInteractable();
				}

				return;
			}
		}
	}

	CouldnotFindInteractable();

}

void ACPlayer::CouldnotFindInteractable()
{
	if (InteractionData.ViewedInteractionComponent)
	{
		InteractionData.ViewedInteractionComponent->SetHiddenInGame(true);
	}
}

void ACPlayer::FoundNewInteractable(UCInteractionComponent* Interactable)
{
	if (Interactable)
	{
		Interactable->SetHiddenInGame(false);
		InteractionData.ViewedInteractionComponent = Interactable;
	}
}

void ACPlayer::BeginInteract()
{
	if (!HasAuthority())
	{
		SeverBeginInteract();
	}

	InteractionData.bInteractHeld = true;

	if (UCInteractionComponent* Interactable = GetInteractable())
	{
		Interactable->BeginInteract(this);

		if (FMath::IsNearlyZero(Interactable->InteractionTime))
		{
			Interact();
		}
		else
		{
			GetWorldTimerManager().SetTimer(TimerHandle_Interact, this, &ACPlayer::Interact, Interactable->InteractionTime, false);
		}
	}
}

void ACPlayer::EndInteract()
{
	if (!HasAuthority())
	{
		SeverEndInteract();
	}

	InteractionData.bInteractHeld = false;

	GetWorldTimerManager().ClearTimer(TimerHandle_Interact);

	if (UCInteractionComponent* Interactable = GetInteractable())
	{
		Interactable->EndInteract(this);
	}

}

void ACPlayer::SeverBeginInteract_Implementation()
{
	BeginInteract();
}

bool ACPlayer::SeverBeginInteract_Validate()
{
	return true;
}

void ACPlayer::SeverEndInteract_Implementation()
{
	EndInteract();
}

bool ACPlayer::SeverEndInteract_Validate()
{
	return true;
}

void ACPlayer::Interact()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interact);

	if(UCInteractionComponent* Interactable = GetInteractable())
	{
		Interactable->Interact(this);
	}
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
	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &ACPlayer::BeginInteract);
	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Released, this, &ACPlayer::EndInteract);

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

void ACPlayer::UseItem(UCItem* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->OnUse(this);
	}
}



