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
#include "Widget/CPlayerHealthWidget.h"
#include "Widget/CSelectActionWidget_Group.h"
#include "Widget/CSelectActionWidget_Icon.h"
#include "Menu/CBackQuitMenu.h"
//#include "PaperSpriteComponent.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create CharacterComponent
	CHelpers::CreateActorComponent(this, &Action, "Action");
	CHelpers::CreateActorComponent(this, &Status, "Status");
	CHelpers::CreateActorComponent(this, &Montages, "Montages");
	CHelpers::CreateActorComponent(this, &State, "State");
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

	// Get Widget Class Asset
	CHelpers::GetClass<UCPlayerHealthWidget>(&HealthWidgetClass, "WidgetBlueprint'/Game/Widget/HealthWidget/WB_CPlayerHealthWidget.WB_CPlayerHealthWidget_C'");
	
	CHelpers::GetClass<UCSelectActionWidget_Group>(&SelectActionWidgetClass, "WidgetBlueprint'/Game/Widget/Skill/WB_SelectAction_Group.WB_SelectAction_Group_C'");

	CHelpers::GetClass<UCBackQuitMenu>(&BackQuitMenuClass, "WidgetBlueprint'/Game/Widget/Menu/WB_BackQuitMenu.WB_BackQuitMenu_C'");


	//<SpringArm>
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 200.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetRelativeLocation(FVector(0, 0, 60));
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 100.f;

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

	// player���� 20���� ������ ������ 80kg������ ���Ը� ���� �̺��� ���� 
	PlayerInventory = CreateDefaultSubobject<UCInventoryComponent>("PlayerInventory");
	PlayerInventory->SetCapacity(20);
	PlayerInventory->SetWeightCapcity(80.f);
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	Action->SetUnarmedMode();

	//Get Material Asset
	UMaterialInstanceConstant* firstMaterialAsset;
	CHelpers::GetAssetDynamic(&firstMaterialAsset, "MaterialInstanceConstant'/Game/Material/MI_Player_Dissolve.MI_Player_Dissolve'");

	UMaterialInstanceConstant* secondMaterialAsset;
	CHelpers::GetAssetDynamic(&secondMaterialAsset, "MaterialInstanceConstant'/Game/Material/MI_Player_Dissolve_2.MI_Player_Dissolve_2'");

	//Create Dynamic Material
	Material_First = UMaterialInstanceDynamic::Create(firstMaterialAsset, nullptr);
	Material_Second = UMaterialInstanceDynamic::Create(secondMaterialAsset, nullptr);

	//Set Dynamic Material to Mesh Comp
	GetMesh()->SetMaterial(0, Material_First);
	GetMesh()->SetMaterial(1, Material_Second);

	// Create Widgets
	HealthWidget = Cast<UCPlayerHealthWidget>(CreateWidget(GetController<APlayerController>(), HealthWidgetClass));
	CheckNull(HealthWidget);
	HealthWidget->AddToViewport();

	BackQuitMenu = Cast<UCBackQuitMenu>(CreateWidget(GetController<APlayerController>(), BackQuitMenuClass));
	CheckNull(BackQuitMenu);
	BackQuitMenu->AddToViewport();
	BackQuitMenu->SetVisibility(ESlateVisibility::Hidden);

	SelectActionWidget = Cast<UCSelectActionWidget_Group>(CreateWidget(GetController<APlayerController>(), SelectActionWidgetClass));
	CheckNull(SelectActionWidget);
	SelectActionWidget->AddToViewport();
	SelectActionWidget->SetVisibility(ESlateVisibility::Hidden);

	// Bind SelectAction Widget Event
	SelectActionWidget->GetChildWidget("Icon1")->OnImageButtonPressed.AddDynamic(this, &ACPlayer::OnFist_Server);
	SelectActionWidget->GetChildWidget("Icon2")->OnImageButtonPressed.AddDynamic(this, &ACPlayer::OnSword_Server);
	SelectActionWidget->GetChildWidget("Icon3")->OnImageButtonPressed.AddDynamic(this, &ACPlayer::OnSniper_Server);

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
	
	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Orange);

	if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		// ��ȣ�ۿ밡���� object�� Check
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
		//CLog::Print("Im Client");
		SeverBeginInteract();
	}

	/** ����ȭ�μ� ������ �츮�� �׸�� ��ȣ�ۿ��� ������ �Ŀ� �׸��� ���� �ִ����� Ȯ���մϴ�.
    �̷��� �ϸ� ��ȣ�ۿ� ������ �׸� ���� �� ƽ���� Ȯ���ϴ� ������ ������ �� �ֽ��ϴ�.
    ���ܴ� �ν���Ʈ�� �ƴ� ��ȣ�ۿ��Դϴ�.
    �� ��� ������ ��ȣ �ۿ� �Ⱓ ���� ��� ƽ�� Ȯ���մϴ�.*/
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
			bsword = true;
			if (Action->DataAssets[(int32)EActionType::Sword]->Weapon != nullptr)
			{
				Action->DataAssets[(int32)EActionType::Sword]->Weapon->Attachment("Holster_OneHand");

				// Random�� �������� -> UActorFactory -> Actor�� Spawn�����ִ°� -> �������� ���� �ٲٸ� ���� ���� ������ �� ����
			}
		}

		else if (Item->Rarity == EItemRarity::IR_Legendary)
		{
			bsniper = true;
			if (Action->DataAssets[(int32)EActionType::Sniper]->Weapon != nullptr)
			{
				Action->DataAssets[(int32)EActionType::Sniper]->Weapon->Attachment("Holster_M14");
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
			// ESpawnActorCollisionHandlingMethod : ���Ͱ� ���� �浹�� ����ϴ� ������� �����Ǵ� ��츦 ó���ϱ� ���� ��� ������ ������ ����
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			// ���� ������ ������ġ
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
	PlayerInputComponent->BindAction("Action", EInputEvent::IE_Pressed, this, &ACPlayer::DoAction_Server);

	// Condition Event
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim);
	
	// Weapon Event
	PlayerInputComponent->BindAction("Fist", EInputEvent::IE_Pressed, this, &ACPlayer::OnFist_Server);
	PlayerInputComponent->BindAction("Sword", EInputEvent::IE_Pressed, this, &ACPlayer::OnSword_Server);
	PlayerInputComponent->BindAction("Sniper", EInputEvent::IE_Pressed, this, &ACPlayer::OnSniper_Server);

	// Select Weapon
	PlayerInputComponent->BindAction("SelectAction", EInputEvent::IE_Pressed, this, &ACPlayer::OnSelectAction);
	PlayerInputComponent->BindAction("SelectAction", EInputEvent::IE_Released, this, &ACPlayer::OffSelectAction);

	PlayerInputComponent->BindAction("BackButton", EInputEvent::IE_Pressed, this, &ACPlayer::BackQuitMenu_Back_Action);
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

void ACPlayer::OnSprint_Implementation()
{
	//GetCharacterMovement()->MaxWalkSpeed = 600.f;
	Status->ChangeMoveSpeed(EWalkSpeedType::Run);
}

void ACPlayer::OffSprint_Implementation()
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

float ACPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	//Attacker = EventInstigator->GetCharacter();
	//Causer = DamageCauser;

	Status->DecreaseHealth(DamageValue);
	HealthWidget->UpdateHealth_Client();

	// Dead
	if (Status->IsDead())
	{
		State->SetDeadMode_Server();
		Dead_Implementation();
		return DamageValue;
	}
	State->SetHittedMode_Server();
	Hitted_Implementation();

	return DamageValue;
}

void ACPlayer::Hitted_Implementation()
{
	Montages->PlayHitted();
}

void ACPlayer::Dead_Implementation()
{
	playerDead = true;

	CheckFalse(State->IsDeadMode());

	// Disable Input
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	CheckNull(controller);

	DisableInput(controller);

	// Play Dead Montage
	Montages->PlayDead();

	// �浹ü ���� ����
	Action->OffAllCollisions();
	GetCapsuleComponent()->SetCollisionProfileName("Spectator");

	UKismetSystemLibrary::K2_SetTimer(this, "End_Dead", 5.f, false);
}

void ACPlayer::End_Dead()
{
	Action->End_Dead();

	PrintLine();
	//CLog::Log("You Died");
	//CLog::Print("You Died");

}

void ACPlayer::DoAction_Server_Implementation()
{
	DoAction();
}

void ACPlayer::DoAction_Implementation()
{
	Action->DoAction();
}


void ACPlayer::OnAim()
{
	Action->DoAim(true);
}

void ACPlayer::OffAim()
{
	Action->DoAim(false);
}

void ACPlayer::OnFist_Implementation()
{
	CheckFalse(State->IsIdleMode());

	Action->SetFistMode();
}

void ACPlayer::OnSword_Implementation()
{
	CheckFalse(State->IsIdleMode());
	CheckFalse(bsword);

	Action->SetSwordMode();
}

void ACPlayer::OnSniper_Implementation()
{
	CheckFalse(State->IsIdleMode());
	CheckFalse(bsniper);

	Action->SetSniperMode();
}

void ACPlayer::OnFist_Server_Implementation()
{
	OnFist();
}

void ACPlayer::OnSword_Server_Implementation()
{
	OnSword();
}

void ACPlayer::OnSniper_Server_Implementation()
{
	OnSniper();
}

void ACPlayer::OnSelectAction()
{
	CheckFalse(State->IsIdleMode());
	
	SelectActionWidget->SetVisibility(ESlateVisibility::Visible);
	GetController<APlayerController>()->bShowMouseCursor = true;
	GetController<APlayerController>()->SetInputMode(FInputModeGameAndUI());
}

void ACPlayer::OffSelectAction()
{
	SelectActionWidget->SetVisibility(ESlateVisibility::Hidden);
	GetController<APlayerController>()->bShowMouseCursor = false;
	GetController<APlayerController>()->SetInputMode(FInputModeGameOnly());
}

void ACPlayer::BackQuitMenu_Back_Action()
{
	BackQuitMenu->SetVisibility(ESlateVisibility::Visible);
	GetController<APlayerController>()->bShowMouseCursor = true;
	GetController<APlayerController>()->SetInputMode(FInputModeUIOnly());
}

void ACPlayer::SetMainWidget()
{

}

FGenericTeamId ACPlayer::GetGenericTeamId() const
{
	return FGenericTeamId(PlayerTeamID);
}

//Todo.. RPC