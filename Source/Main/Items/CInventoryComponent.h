#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAIN_API UCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCInventoryComponent();

	virtual void BeginPlay() override;

	bool AddItem(class UCItem* Item);
	bool RemoveItem(class UCItem* Item);

	UPROPERTY(EditDefaultsOnly, Instanced)
		TArray<class UCItem*> DefaultItems;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
		int32 Capacity;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Items")
		TArray<class UCItem*> Items;

};
