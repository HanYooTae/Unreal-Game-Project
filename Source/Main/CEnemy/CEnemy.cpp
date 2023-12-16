#include "CEnemy/CEnemy.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "CharacterComponents/CActionComponent.h"
#include "CharacterComponents/CMontagesComponent.h"
#include "CharacterComponents/CStatusComponent.h"
#include "Widget/CEnemyHealthWidget.h"

ACEnemy::ACEnemy()
{
	//Create Scene Component
	CHelpers::CreateSceneComponent(this, &HealthWidget, "HealthWidget", GetMesh());
	
	//Create Actor Component
	CHelpers::CreateActorComponent(this, &Action, "Action");
	CHelpers::CreateActorComponent(this, &Status, "Status");
	CHelpers::CreateActorComponent(this, &Montages, "Montages");
	CHelpers::CreateActorComponent(this, &State, "State");
	
	//Component Settings
	// -> MeshComp
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	USkeletalMesh* meshAsset;
	CHelpers::GetAsset(&meshAsset, "SkeletalMesh'/Game/Character/Enemy/Mesh/SK_Goblin_ice.SK_Goblin_ice'");
	GetMesh()->SetSkeletalMesh(meshAsset);
	
	TSubclassOf<UAnimInstance> animInstanceClass;
	CHelpers::GetClass(&animInstanceClass, "AnimBlueprint'/Game/Character/Enemy/Animation/ABP_Goblin.ABP_Goblin_C'");
	GetMesh()->SetAnimInstanceClass(animInstanceClass);
	
	// -> MovementComp
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->MaxWalkSpeed = Status->GetRunSpeed();

	// -> WidgetComp
	TSubclassOf<UCEnemyHealthWidget> healthWidgetClass;
	CHelpers::GetClass(&healthWidgetClass, "WidgetBlueprint'/Game/Widget/HealthWidget/WB_CEnemyHealthWidget.WB_CEnemyHealthWidget_C'");
	HealthWidget->SetWidgetClass(healthWidgetClass);
	HealthWidget->SetRelativeLocation(FVector(0, 0, 180));
	HealthWidget->SetDrawSize(FVector2D(120, 20));
	HealthWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

void ACEnemy::BeginPlay()
{
	//Create Dynamic Material
	LowerMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), nullptr);
	UpperMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(1), nullptr);
	GetMesh()->SetMaterial(0, LowerMaterial);
	GetMesh()->SetMaterial(1, UpperMaterial);
	
	State->OnStateTypeChanged.AddDynamic(this, &ACEnemy::OnStateTypeChanged);
	
	Super::BeginPlay();
	
	//Widget Settings
	HealthWidget->InitWidget();
	UCEnemyHealthWidget* healthWidget = Cast<UCEnemyHealthWidget>(HealthWidget->GetUserWidgetObject());

	if (!!healthWidget)
		healthWidget->UpdateHealth(Status->GetCurrentHealth(), Status->GetMaxHealth());
}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	//Attacker = EventInstigator->GetCharacter();
	//Causer = DamageCauser;

	Status->DecreaseHealth(DamageValue);

	// Dead
	if (Status->IsDead())
	{
		State->SetDeadMode();
		return DamageValue;
	}

	State->SetHittedMode();

	return DamageValue;
}

void ACEnemy::Hitted_Implementation()
{
	// Apply Health Widget
	UCEnemyHealthWidget* healthWidget = Cast<UCEnemyHealthWidget>(HealthWidget->GetUserWidgetObject());
	if (!!healthWidget)
		healthWidget->UpdateHealth(Status->GetCurrentHealth(), Status->GetMaxHealth());

	// Play Hit Montage
	Montages->PlayHitted();

	// Look at Attacker
	/*FVector start = GetActorLocation();
	FVector target = Attacker->GetActorLocation();
	FRotator rotation = FRotator(0, UKismetMathLibrary::FindLookAtRotation(start, target).Yaw, 0);
	SetActorRotation(rotation);*/

	// Hit Back

}

void ACEnemy::Dead_Implementation()
{
	HealthWidget->SetVisibility(false);

	dead = true;

	// Ragdoll
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->GlobalAnimRateScale = 0.f;

	// Add Force
	/*FVector start = GetActorLocation();
	FVector target = Attacker->GetActorLocation();
	FVector direction = (start - target).GetSafeNormal();
	FVector force = direction * LaunchValue * DamageValue * 3000.f;
	GetMesh()->AddForceAtLocation(force, start);*/

	// Off All Collisions
	Action->OffAllCollisions();

	// Destroy All(Attachment, Equipment, DoAction...)
	UKismetSystemLibrary::K2_SetTimer(this, "End_Dead", 5.f, false);
}

void ACEnemy::End_Dead_Implementation()
{
	Action->End_Dead();

	Destroy();
}

void ACEnemy::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::Hitted:	Hitted();	 break;
	case EStateType::Dead:		Dead();		 break;
	}

}

