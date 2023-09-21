#include "Inventory/CPickup.h"
#include "Inventory/CItem.h"
#include "Net/UnrealNetwork.h"
#include "CPlayer/CPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "ActorComponent/CInteractionComponent.h"
#include "ActorComponent/CInventoryComponent.h"
#include "Global.h"
#include "Engine/ActorChannel.h"

ACPickup::ACPickup()
{
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	PickupMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	SetRootComponent(PickupMesh);

	InteractionComp = CreateDefaultSubobject<UCInteractionComponent>("PickupInteractionComponent");
	InteractionComp->InteractionTime = 0.5f;
	InteractionComp->InteractionDistance = 200.f;
	InteractionComp->InteractableNameText = FText::FromString("Pickup");
	InteractionComp->InteractableActionText = FText::FromString("Take");
	InteractionComp->OnInteract.AddDynamic(this, &ACPickup::OnTakePickup);
	InteractionComp->SetupAttachment(PickupMesh);

	SetReplicates(true);
}

void ACPickup::InitializePickup(const TSubclassOf<class UCItem> ItemClass, const int32 Quantity)
{
	if (HasAuthority() && ItemClass && Quantity > 0)
	{
		Item = NewObject<UCItem>(this, ItemClass);
		Item->SetQuantity(Quantity);

		OnRep_Item();

		Item->MarkDirtyForReplication();
	}
}

//void ACPickup::AlignWithGround()
//{
//}

void ACPickup::OnRep_Item()
{
	if (Item)
	{
		PickupMesh->SetStaticMesh(Item->PickupMesh);
		InteractionComp->InteractableNameText = Item->ItemDisplayName;

		//클라이언트는 항목 수량 변경 시 interaction 위젯을 새로 고치기 위해 이 delegate에 bind
		Item->OnItemModified.AddDynamic(this, &ACPickup::InItemModified);
	}
	//항목의 복제된 속성이 변경되면 위젯을 새로고친다
	InteractionComp->RefreshWidget();
}

void ACPickup::InItemModified()
{
	if (InteractionComp)
	{
		InteractionComp->RefreshWidget();
	}
}

void ACPickup::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority() && ItemTemplate && bNetStartup)
	{
		InitializePickup(ItemTemplate->GetClass(), ItemTemplate->GetQuantity());
	}
	
	//픽업이 runtime에 생성된 경우 드롭된 지면의 rotation과 일치하는지 확인
	//20도 경사에 픽업을 떨어뜨리면 픽업도 20도 각도로 생성
	if (!bNetStartup)
	{
		AlignWithGround();
	}

	if (Item)
	{
		Item->MarkDirtyForReplication();
	}
}

void ACPickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACPickup, Item);
}

bool ACPickup::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (Item && Channel->KeyNeedsToReplicate(Item->GetUniqueID(), Item->RepKey))
	{
		bWroteSomething |= Channel->ReplicateSubobject(Item, *Bunch, *RepFlags);
	}
	

	return bWroteSomething;
}

#if WITH_EDITOR
void ACPickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	// editor에서 새 픽업을 선택한 경우 선택 중인 새 항목을 반영하도록 메시를 변경
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ACPickup, ItemTemplate))
	{
		if (ItemTemplate)
		{
			PickupMesh->SetStaticMesh(ItemTemplate->PickupMesh);
		}
	}
}
#endif

void ACPickup::OnTakePickup(ACPlayer* Taker)
{
	if (!Taker)
	{
		CLog::Print("얻었지만 사용자가 존재하지 않는다.");
		return;
	}

	//Pending Kill이 필요하다고 100% 확신할 수는 없지만 다른 플레이어가 이미 가져가려고 시도한 픽업을 플레이어가 가져가는 것을 방지
	if (HasAuthority() && !IsPendingKillPending() && Item)
	{
		if (UCInventoryComponent* PlayerInv = Taker->PlayerInventory)
		{
			const FItemAddResult AddResult = PlayerInv->TryAddItem(Item);

			if (AddResult.ActualAmountGiven < Item->GetQuantity())
			{
				Item->SetQuantity(Item->GetQuantity() - AddResult.ActualAmountGiven);
			}
			else if (AddResult.ActualAmountGiven >= Item->GetQuantity())
			{
				Destroy();
			}
		}
	}
}


