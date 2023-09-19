#pragma once

#include "CoreMinimal.h"
#include "../Inventory/CItem.h"
#include "Components/ActorComponent.h"
#include "CInventoryComponent.generated.h"

// 인벤토리내부가 바뀌거나 UI가 업데이트가 될때 실행
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UENUM(BlueprintType)
enum class EItemAddResult : uint8
{
	IAR_NoItemsAdded UMETA(DisplayName = "No items added"),
	IAR_SomeItemsAdded UMETA(DisplayName = "Some items added"),
	IAR_AllItemsAdded UMETA(DisplayName = "All items added")
};

USTRUCT(BlueprintType)
struct FItemAddResult
{
	GENERATED_BODY()

public:
	FItemAddResult() {};
	FItemAddResult(int32 InItemQuantity) : AmountToGive(InItemQuantity), ActualAmountGiven(0) {};
	FItemAddResult(int32 InItemQuantity, int32 InQuantityAdded) : AmountToGive(InItemQuantity), ActualAmountGiven(InQuantityAdded) {};

	// 갯수증가를 도울 변수
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
		int32 AmountToGive;

	// 정해진 무게, 최대 획득갯수에 맞게 Item추가를 도울 변수
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
		int32 ActualAmountGiven;

	// 결과값
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
		EItemAddResult Result;

	// 무게보다 더 많거나 용량이 많으면 알려주는 Text
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
		FText ErrorText;

	// Helpers
	static FItemAddResult AddedNone(const int32 InItemQuantity, const FText& ErrorText)
	{
		FItemAddResult AddedNoneResult(InItemQuantity);
		AddedNoneResult.Result = EItemAddResult::IAR_NoItemsAdded;
		AddedNoneResult.ErrorText = ErrorText;

		return AddedNoneResult;
	}

	static FItemAddResult AddedSome(const int32 InItemQuantity, const int32 ActualAmountGiven, const FText& ErrorText)
	{
		FItemAddResult AddedSomeResult(InItemQuantity, ActualAmountGiven);
		AddedSomeResult.Result = EItemAddResult::IAR_SomeItemsAdded;
		AddedSomeResult.ErrorText = ErrorText;

		return AddedSomeResult;
	}

	static FItemAddResult AddedAll(const int32 InItemQuantity)
	{
		FItemAddResult AddAllResult(InItemQuantity, InItemQuantity);
		AddAllResult.Result = EItemAddResult::IAR_AllItemsAdded;

		return AddAllResult;
	}
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MAIN_API UCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

		friend class UCItem;
public:
	UCInventoryComponent();

public:
	// Inventory에 아이템 추가
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		FItemAddResult TryAddItem(class UCItem* Item);

	// 아이템 인스턴스 대신 아이템 클래스를 사용하여 인벤토리에 아이템 추가
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		FItemAddResult TryAddItemFromClass(TSubclassOf<class UCItem> ItemClass, const int32 Quantity);

	// 품목에서 일부 수량을 빼내고 수량이 0이 되면 재고에서 제거합니다.
	int32 ConsumeItem(class UCItem* Item);
	int32 ConsumeItem(class UCItem* Item, const int32 Quantity);

	// inventory 에서 Item이동
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool RemoveItem(class UCItem* Item);

	// 아이템을 가지고 있다면 return값은 true
	UFUNCTION(BlueprintPure, Category = "Inventory")
		bool HasItem(TSubclassOf<class UCItem> ItemClass, const int32 Quantity = 1) const;

	// 얻은 아이템이 이미 가진 아이템의 class와 동일한지를 반환하는함수
	UFUNCTION(BlueprintPure, Category = "Inventory")
		UCItem* FindItem(class UCItem* Item) const;

	// 얻은 아이템class가 이미 가진 아이템의 class와 동일한지를 반환하는함수
	UFUNCTION(BlueprintPure, Category = "Inventory")
		UCItem* FindItemByClass(TSubclassOf<class UCItem> ItemClass) const;

	// 모든 인벤의 아이템 클레스를 가져옴
	UFUNCTION(BlueprintPure, Category = "Inventory")
		TArray<UCItem*> FindItemsByClass(TSubclassOf<class UCItem> ItemClass) const;

	// 현재의 무개와 아이템 갯수 를 가져옴 GetItems().Num()의 역활을 한다.
	UFUNCTION(BlueprintPure, Category = "Inventory")
		float GetCurrentWeight() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void SetWeightCapcity(const float NewWeightCapacity);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void SetCapacity(const int32 NewCapacity);

	UFUNCTION(Client, Reliable)
		void ClientRefreshInventory();
	void ClientRefreshInventory_Implementation();
private:
	// non_BP 노출 항목 추가 함수, 바로 호출 불가능 무조건 TryAddItem(), TryAddItemFromClass()를 사용해야함
	FItemAddResult TryAddItem_Internal(class UCItem* Item);

	// Items.Add()를 대신할 함수
	UCItem* AddItem(class UCItem* Item);

public:
	UFUNCTION(BlueprintPure, Category = "Inventory")
		FORCEINLINE float GetWeightCapacity() const { return WeightCapacity; }

	UFUNCTION(BlueprintPure, Category = "Inventory")
		FORCEINLINE int32 GetCapacity() const { return Capacity; }

	UFUNCTION(BlueprintPure, Category = "Inventory")
		FORCEINLINE TArray<class UCItem*> GetItems() const { return Items; }

public:
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FOnInventoryUpdated OnInventoryUpdated;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory")
		float WeightCapacity;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory", meta = (ClampMax = 200.0, ClampMin = 0.0))
		int32 Capacity;

	UPROPERTY(VisibleAnywhere, Category = "Inventory", ReplicatedUsing = "OnRep_Items")
		TArray<class UCItem*> Items;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags);

private:
	UFUNCTION()
		void OnRep_Items();

	UPROPERTY()
		int32 ReplicatedItemsKey;
};
