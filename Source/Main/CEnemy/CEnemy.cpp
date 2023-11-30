#include "CEnemy/CEnemy.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "CharacterComponents/CActionComponent.h"
#include "CharacterComponents/CMontagesComponent.h"
#include "CharacterComponents/CStatusComponent.h"

ACEnemy::ACEnemy()
{
	//Create Scene Component
	
	//Create Actor Component
	CHelpers::CreateActorComponent(this, &Action, "Action");
	CHelpers::CreateActorComponent(this, &Montages, "Montages");
	CHelpers::CreateActorComponent(this, &State, "State");
	CHelpers::CreateActorComponent(this, &Status, "Status");
	
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
}

//float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
//{
//}

void ACEnemy::Hitted()
{
}

void ACEnemy::Dead()
{
}

void ACEnemy::End_Dead()
{
}

void ACEnemy::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
}

