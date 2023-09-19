#pragma once

#include "CoreMinimal.h"
#include "../Inventory/CItem.h"
#include "Components/ActorComponent.h"
#include "CInventoryComponent.generated.h"

// �κ��丮���ΰ� �ٲ�ų� UI�� ������Ʈ�� �ɶ� ����
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

	// ���������� ���� ����
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
		int32 AmountToGive;

	// ������ ����, �ִ� ȹ�氹���� �°� Item�߰��� ���� ����
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
		int32 ActualAmountGiven;

	// �����
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
		EItemAddResult Result;

	// ���Ժ��� �� ���ų� �뷮�� ������ �˷��ִ� Text
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
	// Inventory�� ������ �߰�
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		FItemAddResult TryAddItem(class UCItem* Item);

	// ������ �ν��Ͻ� ��� ������ Ŭ������ ����Ͽ� �κ��丮�� ������ �߰�
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		FItemAddResult TryAddItemFromClass(TSubclassOf<class UCItem> ItemClass, const int32 Quantity);

	// ǰ�񿡼� �Ϻ� ������ ������ ������ 0�� �Ǹ� ����� �����մϴ�.
	int32 ConsumeItem(class UCItem* Item);
	int32 ConsumeItem(class UCItem* Item, const int32 Quantity);

	// inventory ���� Item�̵�
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool RemoveItem(class UCItem* Item);

	// �������� ������ �ִٸ� return���� true
	UFUNCTION(BlueprintPure, Category = "Inventory")
		bool HasItem(TSubclassOf<class UCItem> ItemClass, const int32 Quantity = 1) const;

	// ���� �������� �̹� ���� �������� class�� ���������� ��ȯ�ϴ��Լ�
	UFUNCTION(BlueprintPure, Category = "Inventory")
		UCItem* FindItem(class UCItem* Item) const;

	// ���� ������class�� �̹� ���� �������� class�� ���������� ��ȯ�ϴ��Լ�
	UFUNCTION(BlueprintPure, Category = "Inventory")
		UCItem* FindItemByClass(TSubclassOf<class UCItem> ItemClass) const;

	// ��� �κ��� ������ Ŭ������ ������
	UFUNCTION(BlueprintPure, Category = "Inventory")
		TArray<UCItem*> FindItemsByClass(TSubclassOf<class UCItem> ItemClass) const;

	// ������ ������ ������ ���� �� ������ GetItems().Num()�� ��Ȱ�� �Ѵ�.
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
	// non_BP ���� �׸� �߰� �Լ�, �ٷ� ȣ�� �Ұ��� ������ TryAddItem(), TryAddItemFromClass()�� ����ؾ���
	FItemAddResult TryAddItem_Internal(class UCItem* Item);

	// Items.Add()�� ����� �Լ�
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
