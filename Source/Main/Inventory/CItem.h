#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemModified);

UENUM(BlueprintType)
enum class EItemRarity : uint8 // 나중에 조정 딱히 필요없음
{
	IR_Common UMETA(DisplayName = "Common"),
	IR_UnCommon UMETA(DisplayName = "Uncommon"),
	IR_Rare UMETA(DisplayName = "Rare"),
	IR_VeryRare UMETA(DisplayName = "very Rare"),
	IR_Legendary UMETA(DisplayName = "Legendary")
};

UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew)
class MAIN_API UCItem : public UObject
{
	GENERATED_BODY()
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const;
	virtual bool IsSupportedForNetworking() const;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
#endif

public:
	UCItem();

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item")
		class UStaticMesh* PickupMesh;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item")
		class UTexture2D* Thumbnail;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item")
		FText ItemDisplayName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item", meta = (MultiLine = true))
		FText ItemDescription;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item")
		FText UseActionText;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item")
		EItemRarity Rarity;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item", meta = (ClampMin = 0.0))
		float Weight;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item")
		bool bStackable;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item", meta = (ClampMin = 2.00, EditCondition = "bStackable"))
		int32 MaxStackSize;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item")
		TSubclassOf<class UItemTooltip> ItemTooltip;

	UPROPERTY(EditAnywhere, Category = "Item", ReplicatedUsing = "OnRep_Quantity", meta = (EditCondition = "bStackable", UIMin = 1.00))
		int32 Quantity;

	UPROPERTY()
		class UCInventoryComponent* OwningInventory;

	// 인벤토리 항목을 효율적으로 복제하는 데 사용
	UPROPERTY()
		int32 RepKey;

	UPROPERTY(BlueprintAssignable)
		FOnItemModified OnItemModified;

	UFUNCTION()
		void OnRep_Quantity();

	UFUNCTION(BlueprintCallable, Category = "Item")
		void SetQuantity(const int32 NewQuantity);

	UFUNCTION(BlueprintPure, Category = "Item")
		FORCEINLINE int32 GetQuantity() const { return Quantity; }

	UFUNCTION(BlueprintCallable, Category = "Item")
		FORCEINLINE float GetStackWeight() const { return Quantity * Weight; }

	UFUNCTION(BlueprintPure, Category = "Item")
		virtual bool ShouldShowInInventory() const;

	virtual void Use(class ACPlayer* Character);
	virtual void AddedToInventory(class UCInventoryComponent* Inventory);

	//개체를 복제가 필요한 것으로 표시합니다.복제된 속성을 수정한 후에는 이를 내부적으로 호출해야 합니다.
	void MarkDirtyForReplication();
};
