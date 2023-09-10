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

	// 표현할 항목을 가져와서 해당 항목에서 사진을 만듭니다.Beginplay에서 완료되고 플레이어가 땅에 아이템을 떨어뜨릴 때 완료됩니다.
	void InitializePickup(const TSubclassOf<class UCItem> ItemClass, const int32 Quantity);

	//픽업 rotarion을 지면 rotarion과 정렬
	UFUNCTION(BlueprintImplementableEvent)
		void AlignWithGround();

	// 이는 생성될 때 픽업을 생성하기 위한 템플릿으로 사용
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
		class UCItem* ItemTemplate;

protected:

	// 아이템을 주웠을때 인벤에 추가되도록 하는 변수
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, ReplicatedUsing = "OnRep_Item")
		class UCItem* Item;

	UFUNCTION()
		void OnRep_Item();

	// 항목의 일부 속성이 수정되면 이를 InItemModified에 바인딩하고 항목이 수정되면 UI를 새로 고칩니다.
	UFUNCTION()
		void InItemModified();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch *Bunch, FReplicationFlags* RepFlags);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	// 주울때 호출
	UFUNCTION()
		void OnTakePickup(class ACPlayer* Taker);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components")
		class UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		class UCInteractionComponent* InteractionComp;

};
