#include "CPlayer/CPlayer.h"
#include "Global.h"
#include "CAnimInstance.h"
#include "Widget/CMainWidget.h"
#include "Components/CapsuleComponent.h"
#include "CharacterComponents/CStatusComponent.h"
#include "CharacterComponents/CStateComponent.h"
#include "CharacterComponents/CMontagesComponent.h"
#include "CharacterComponents/CActionComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"
#include "ActorComponent/CParkourSystem.h"
#include "ActorComponent/CInteractionComponent.h"
#include "ActorComponent/CInventoryComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Inventory/CPickup.h"
#include "Inventory/CWeaponsItem.h"
#include "Actions/CWeapon_Sniper.h"
#include "Actions/CWeapon_Sword.h"
#include "Actions/CActionData.h"
//#include "PaperSpriteComponent.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create CharacterComponent
	CHelpers::CreateActorComponent(this, &Action, "Action");
	CHelpers::CreateActorComponent(this, &Status, "Status");
	CHelpers::CreateActorComponent(this, &State, "State");
	CHelpers::CreateActorComponent(this, &Montages, "Montages");\
	CHelpers::CreateActorComponent(this, &parkour, "ACParkour");
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	ConstructorHelpers::FObjectFinder<USkeletalMesh> meshAsset(TEXT("SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (meshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(meshAsset.Object);
	
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	ConstructorHelpers::FClassFinder<UCAnimInstance> animClass(TEXT("AnimBlueprint'/Game/Character/Heraklios/Animation/ABP_MyCPlayer.ABP_MyCPlayer_C'"));
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

	// Interaction
	InteractionCheckFrequency = 0.f;
	InteractionCheckDistance = 3000.f;

	// player에게 20개의 슬롯을 가지며 80kg정도의 무게를 가진 이벤을 설정 
	PlayerInventory = CreateDefaultSubobject<UCInventoryComponent>("PlayerInventory");
	PlayerInventory->SetCapacity(20);
	PlayerInventory->SetWeightCapcity(80.f);
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	// Use CharacterComponents Delegate
	State->OnStateTypeChanged.AddDynamic(this, &ACPlayer::OnStateTypeChanged);
	Action->SetUnarmedMode();

	//Get Material Asset
	UMaterialInstanceConstant* firstMaterialAsset;
	CHelpers::GetAssetDynamic(&firstMaterialAsset, "MaterialInstanceConstant'/Game/Character/Heraklios/Material/BattalionLeader_MAT_Inst.BattalionLeader_MAT_Inst'");

	UMaterialInstanceConstant* secondMaterialAsset;
	CHelpers::GetAssetDynamic(&secondMaterialAsset, "MaterialInstanceConstant'/Game/Character/Heraklios/Material/phong1_Inst.phong1_Inst'");

	//Create Dynamic Material
	Material_First = UMaterialInstanceDynamic::Create(firstMaterialAsset, nullptr);
	Material_Second = UMaterialInstanceDynamic::Create(secondMaterialAsset, nullptr);

	//Set Dynamic Material to Mesh Comp
	GetMesh()->SetMaterial(0, Material_First);
	GetMesh()->SetMaterial(1, Material_Second);

	// Create & Attach MainWidget
	MainWidget = CreateWidget<UCMainWidget>(GetWorld(), MainWidgetClass);
	CheckNull(MainWidget);
	MainWidget->AddToViewport();

	// Hidden Players in Minimap
	CheckNull(RenderMinimap);
	RenderMinimap->ShowFlags.SkeletalMeshes = false;

}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const bool bIsInteractionOnServer = (HasAuthority() && IsInteracting());

	// Check
	if ((HasAuthority() || bIsInteractionOnServer) && GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
	}
}

void ACPlayer::PerformInteractionCheck_Implementation()
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
	
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Orange);

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

void ACPlayer::CouldnotFindInteractable_Implementation()
{
	if (GetWorldTimerManager().IsTimerActive(TimerHandle_Interact))
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interact);
	}

	if (UCInteractionComponent* Interactable = GetInteractable())
	{
		Interactable->EndFocus(this);

		if (InteractionData.bInteractHeld)
		{
			EndInteract();
		}
	}

	InteractionData.ViewedInteractionComponent = nullptr;
}

void ACPlayer::FoundNewInteractable_Implementation(UCInteractionComponent* Interactable)
{
	EndInteract();
	
	if (UCInteractionComponent* oldInteractable = GetInteractable())
	{
		oldInteractable->EndFocus(this);
	}
	
	InteractionData.ViewedInteractionComponent = Interactable;
	Interactable->BeginFocus(this);

}

void ACPlayer::BeginInteract()
{
	if (!HasAuthority())
	{
		CLog::Print("Im Client");
		SeverBeginInteract();
	}

	/** 최적화로서 서버는 우리가 항목과 상호작용을 시작한 후에 항목을 보고 있는지만 확인합니다.
    이렇게 하면 상호작용 가능한 항목에 대해 매 틱마다 확인하는 서버를 절약할 수 있습니다.
    예외는 인스턴트가 아닌 상호작용입니다.
    이 경우 서버는 상호 작용 기간 동안 모든 틱을 확인합니다.*/
	if (HasAuthority())
	{
		PerformInteractionCheck();
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

	if (UCInteractionComponent* Interactable = GetInteractable())
	{
		Interactable->Interact(this);
	}
}

bool ACPlayer::IsInteracting() const
{
	return GetWorldTimerManager().IsTimerActive(TimerHandle_Interact);
}

float ACPlayer::GetRemainingInteractime() const
{
	return GetWorldTimerManager().GetTimerRemaining(TimerHandle_Interact);
}

void ACPlayer::UseItem(class UCItem* Item)
{
	

	if (!HasAuthority() && Item)
	{
		ServerUseItem(Item);
	}

	if (HasAuthority())
	{
		if (PlayerInventory && !PlayerInventory->FindItem(Item))
		{
			return;
		}
	}

	if (Item)
	{
		Item->Use(this);

		if (Item->Rarity == EItemRarity::IR_VeryRare)
		{
			if (Action->DataAssets[(int32)EActionType::Sword]->Weapon != nullptr)
			{
				Action->DataAssets[(int32)EActionType::Sword]->Weapon->Attachment(this, "Holster_OneHand");

				// Random한 아이템을 -> UActorFactory -> Actor를 Spawn시켜주는거 -> 변수값을 조금 바꾸면 여러 개를 스폰할 수 있음
			}
		}

		else if (Item->Rarity == EItemRarity::IR_Legendary)
		{
			if (Action->DataAssets[(int32)EActionType::Sniper]->Weapon != nullptr)
			{
				Action->DataAssets[(int32)EActionType::Sniper]->Weapon->Attachment(this, "Holster_M14");
			}
		}
		
	}
}

void ACPlayer::ServerUseItem_Implementation(class UCItem* Item)
{
	UseItem(Item);
}


void ACPlayer::DropItem(class UCItem* Item, const int32 Quantity)
{
	if (PlayerInventory && Item && PlayerInventory->FindItem(Item))
	{
		if (!HasAuthority())
		{
			ServerDropItem(Item, Quantity);
			return;
		}

		if (HasAuthority())
		{
			const int32 ItemQuantity = Item->GetQuantity();
			const int32 DroppedQuantity = PlayerInventory->ConsumeItem(Item, Quantity);

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.bNoFail = true;
			// ESpawnActorCollisionHandlingMethod : 액터가 차단 충돌을 통과하는 방식으로 생성되는 경우를 처리하기 위해 사용 가능한 전략을 정의
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			// 버린 아이템 스폰위치
			FVector SpawnLocation = GetActorLocation();
			SpawnLocation.Z -= GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

			FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

			ensure(PickupClass);

			if (ACPickup* Pickup = GetWorld()->SpawnActor<ACPickup>(PickupClass, SpawnTransform, SpawnParams))
			{
				Pickup->InitializePickup(Item->GetClass(), DroppedQuantity);
			}
		}
	}
}

void ACPlayer::ServerDropItem_Implementation(class UCItem* Item, const int32 Quantity)
{
	DropItem(Item, Quantity);
}

bool ACPlayer::ServerDropItem_Validate(class UCItem* Item, const int32 Quantity)
{
	return true;
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
	PlayerInputComponent->BindAction("Vaulting", EInputEvent::IE_Pressed, parkour, &UCParkourSystem::Parkour);
	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &ACPlayer::BeginInteract);
	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Released, this, &ACPlayer::EndInteract);
	PlayerInputComponent->BindAction("Action", EInputEvent::IE_Pressed, this, &ACPlayer::OnAction);
	
	// Weapon Event
	PlayerInputComponent->BindAction("Fist", EInputEvent::IE_Pressed, this, &ACPlayer::OnFist);
	PlayerInputComponent->BindAction("Sword", EInputEvent::IE_Pressed, this, &ACPlayer::OnSword);
	PlayerInputComponent->BindAction("Sniper", EInputEvent::IE_Pressed, this, &ACPlayer::OnSniper);
	PlayerInputComponent->BindAction("MagicBall", EInputEvent::IE_Pressed, this, &ACPlayer::OnMagicBall);
	PlayerInputComponent->BindAction("Warp", EInputEvent::IE_Pressed, this, &ACPlayer::OnWarp);
	PlayerInputComponent->BindAction("Storm", EInputEvent::IE_Pressed, this, &ACPlayer::OnStorm);

}

void ACPlayer::OnMoveForward(float Axis)
{
	CheckFalse(Status->IsCanMove());
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	CheckFalse(Status->IsCanMove());
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
	//GetCharacterMovement()->MaxWalkSpeed = 600.f;
	Status->ChangeMoveSpeed(EWalkSpeedType::Run);
}

void ACPlayer::OffSprint()
{
	//GetCharacterMovement()->MaxWalkSpeed = 400.f;
	Status->ChangeMoveSpeed(EWalkSpeedType::Walk);
}

void ACPlayer::StartJump()
{
	bPressedJump = true;
}

void ACPlayer::StopJump()
{
	bPressedJump = false;
}

void ACPlayer::OnAction()
{
	Action->DoAction();
}

void ACPlayer::OnFist()
{
	CheckFalse(State->IsIdleMode());

	Action->SetFistMode();
}

void ACPlayer::OnSword()
{
	CheckFalse(State->IsIdleMode());

	Action->SetSwordMode();
}

void ACPlayer::OnSniper()
{
	CheckFalse(State->IsIdleMode());

	Action->SetSniperMode();
}

void ACPlayer::OnMagicBall()
{
	CheckFalse(State->IsIdleMode());

	Action->SetMagicBallMode();
}

void ACPlayer::OnWarp()
{
	CheckFalse(State->IsIdleMode());

	Action->SetWarpMode();
}

void ACPlayer::OnStorm()
{
	CheckFalse(State->IsIdleMode());

	Action->SetStormMode();
}

void ACPlayer::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{

}

void ACPlayer::SetMainWidget()
{

}