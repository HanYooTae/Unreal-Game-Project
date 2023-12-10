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

		//Ŭ���̾�Ʈ�� �׸� ���� ���� �� interaction ������ ���� ��ġ�� ���� �� delegate�� bind
		Item->OnItemModified.AddDynamic(this, &ACPickup::InItemModified);
	}
	//�׸��� ������ �Ӽ��� ����Ǹ� ������ ���ΰ�ģ��
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
	
	//�Ⱦ��� runtime�� ������ ��� ��ӵ� ������ rotation�� ��ġ�ϴ��� Ȯ��
	//20�� ��翡 �Ⱦ��� ����߸��� �Ⱦ��� 20�� ������ ����
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

	// editor���� �� �Ⱦ��� ������ ��� ���� ���� �� �׸��� �ݿ��ϵ��� �޽ø� ����
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
		CLog::Print("������� ����ڰ� �������� �ʴ´�.");
		return;
	}

	//Pending Kill�� �ʿ��ϴٰ� 100% Ȯ���� ���� ������ �ٸ� �÷��̾ �̹� ���������� �õ��� �Ⱦ��� �÷��̾ �������� ���� ����
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


