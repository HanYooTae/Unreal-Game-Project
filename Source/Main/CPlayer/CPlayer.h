#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

USTRUCT()
struct FInteractionData
{
	GENERATED_BODY()

public:

	FInteractionData()
	{
		ViewedInteractionComponent = nullptr;
		LastInteractionCheckTime = 0.f;
		bInteractHeld = false;
	}

	UPROPERTY()
		class UCInteractionComponent* ViewedInteractionComponent;

	UPROPERTY()
		float LastInteractionCheckTime;

	UPROPERTY()
		bool bInteractHeld;
};

UCLASS()
class MAIN_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
		class UCInventoryComponent* Inventory;

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected: //interact
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
		float InteractionCheckFrequency;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
		float InteractionCheckDistance;

	void PerformInteractionCheck(); // 아래 두 함수 를 실행하는 함수
	void CouldnotFindInteractable();	// 상호작용 하는 물체를 찾지못할경우
	void FoundNewInteractable(UCInteractionComponent* Interactable); // 상호작용하는 물체를 찾았을 경우

	void BeginInteract();
	void EndInteract();

	void Interact();

	UPROPERTY()
		FInteractionData InteractionData;

	FORCEINLINE class UCInteractionComponent* GetInteractable() const { return InteractionData.ViewedInteractionComponent; }

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Animation")
		UAnimMontage* Climb;

private: // Axis
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);

private: // Action
	void OnSprint();
	void OffSprint();

	void StartJump();
	void StopJump();

private: 
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
		class UCParkourSystem* parkour;
		
private:

	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

// Main Widget
public:
	void SetMainWidget();

private:
	TSubclassOf<class UCMainWidget> MainWidgetClass;

	class UCMainWidget* MainWidget;

public: //inventory system
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Health")
		float Health;

	UFUNCTION(BlueprintCallable, Category = "Items")
		void UseItem(class UCItem* Item);


};
