#include "Actions/CEquipment.h"
#include "Global.h"
#include "CharacterComponents/CStatusComponent.h"
#include "CharacterComponents/CStateComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ACEquipment::ACEquipment()
{

}

void ACEquipment::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	StateComp = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	StatusComp = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
}

void ACEquipment::Equip_Implementation()
{
	// Set State Equip
	StateComp->SetEquipMode_Server();

	// bCanMove
	EquipmentData.bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();

	// Play Draw Montage
	if (!!EquipmentData.AnimMontage)
		OwnerCharacter->PlayAnimMontage(EquipmentData.AnimMontage, EquipmentData.PlayRate, EquipmentData.StartSection);

	else
	{
		// ��Ÿ�ְ� ���� ���� ���� ��
		Begin_Equip();

		// ��Ÿ�ְ� ������ Notify�� �����Ƿ� �ٷ� SetIdle
		End_Equip();
	}

	// bPawnControl
	if (EquipmentData.bPawnControl == true)
	{
		OwnerCharacter->bUseControllerRotationYaw = true;
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	}
}

void ACEquipment::Begin_Equip_Implementation()
{
	if (OnBeginEquip.IsBound())
		OnBeginEquip.Broadcast();
}

void ACEquipment::End_Equip_Implementation()
{
	bEquippedThis = true;

	StateComp->SetIdleMode_Server();
	StatusComp->SetMove();
}

void ACEquipment::Unequip_Implementation()
{
	bEquippedThis = false;

	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;

	if (OnUnequip.IsBound())
		OnUnequip.Broadcast();
}
