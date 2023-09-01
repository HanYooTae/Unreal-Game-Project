#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CItem.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class MAIN_API UCItem : public UObject
{
	GENERATED_BODY()

public:
	UCItem();

public:
	virtual class UWorld* GetWorld() const { return World; }

	UPROPERTY(Transient)
		class UWorld* World;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item")
		FText UseActionText;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item")
		class UStaticMesh* pickupMesh;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item")
		class UTexture2D* Thumbnail;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item")
		FText ItemDisplayName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item", meta = (MultiLine = true))
		FText ItemDescription;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item", meta = (ClampMin = 0.0))
		float Weight; // inventory�� ���Ը� �����Ͽ� ������ �Ѽ� �ִ� ���� ���x

	UPROPERTY()
		class UCInventoryComponent* OwningInventory;

	virtual void Use(class ACPlayer* Character);

	UFUNCTION(BlueprintImplementableEvent)
		void OnUse(class ACPlayer* Character);


};
