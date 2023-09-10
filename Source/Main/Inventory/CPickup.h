#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPickup.generated.h"

UCLASS()
class MAIN_API ACPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPickup();

	// ǥ���� �׸��� �����ͼ� �ش� �׸񿡼� ������ ����ϴ�.Beginplay���� �Ϸ�ǰ� �÷��̾ ���� �������� ����߸� �� �Ϸ�˴ϴ�.
	void InitializePickup(const TSubclassOf<class UCItem> ItemClass, const int32 Quantity);

	//�Ⱦ� rotarion�� ���� rotarion�� ����
	UFUNCTION(BlueprintImplementableEvent)
		void AlignWithGround();

	// �̴� ������ �� �Ⱦ��� �����ϱ� ���� ���ø����� ���
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
		class UCItem* ItemTemplate;

protected:

	// �������� �ֿ����� �κ��� �߰��ǵ��� �ϴ� ����
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, ReplicatedUsing = "OnRep_Item")
		class UCItem* Item;

	UFUNCTION()
		void OnRep_Item();

	// �׸��� �Ϻ� �Ӽ��� �����Ǹ� �̸� InItemModified�� ���ε��ϰ� �׸��� �����Ǹ� UI�� ���� ��Ĩ�ϴ�.
	UFUNCTION()
		void InItemModified();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch *Bunch, FReplicationFlags* RepFlags);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	// �ֿﶧ ȣ��
	UFUNCTION()
		void OnTakePickup(class ACPlayer* Taker);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components")
		class UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		class UCInteractionComponent* InteractionComp;

};
