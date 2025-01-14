#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/EngineTypes.h"
#include "GenericTeamAgentInterface.h"
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
class MAIN_API ACPlayer : public ACharacter , public IGenericTeamAgentInterface
{
    GENERATED_BODY()

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

	UFUNCTION(Reliable, Server) //Todo.
        void PerformInteractionCheck(); // 아래 두 함수 를 실행하는 함수
    
	UFUNCTION(NetMulticast, Reliable) //Todo.
        void CouldnotFindInteractable();   // 상호작용 하는 물체를 찾지못할경우
	UFUNCTION(NetMulticast, Reliable) //Todo.
        void FoundNewInteractable(UCInteractionComponent* Interactable); // 상호작용하는 물체를 찾았을 경우

protected:  // Action Event
    void BeginInteract();
    void EndInteract();

    UFUNCTION(Reliable, Server)
        void DoAction_Server();

    UFUNCTION(NetMulticast, Reliable)
        void DoAction();

    void OnAim();
    void OffAim();

	UFUNCTION(Reliable, Server, WithValidation)
        void SeverBeginInteract();
    void SeverBeginInteract_Implementation();
    bool SeverBeginInteract_Validate();

	UFUNCTION(Reliable, Server, WithValidation)
        void SeverEndInteract();
    void SeverEndInteract_Implementation();
    bool SeverEndInteract_Validate();

    void Interact();

private: // Action
    void OnSprint();
    void OffSprint();

    void StartJump();
    void StopJump();

private:
    virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(NetMulticast, Reliable)
        void Hitted();
    void Hitted_Implementation();

	UFUNCTION(NetMulticast, Reliable)
        void Dead();
    void Dead_Implementation();

    UFUNCTION()
        void End_Dead();

private: // Weapon
    UFUNCTION(Reliable, Server)
        void OnFist_Server();
    void OnFist_Server_Implementation();

    UFUNCTION(Reliable, Server)
        void OnSword_Server();
    void OnSword_Server_Implementation();

    UFUNCTION(Reliable, Server)
        void OnSniper_Server();
    void OnSniper_Server_Implementation();

	UFUNCTION(NetMulticast, Reliable)
        void OnFist();
        void OnFist_Implementation();

	UFUNCTION(NetMulticast, Reliable)
        void OnSword();
        void OnSword_Implementation();

	UFUNCTION(NetMulticast, Reliable)
        void OnSniper();
        void OnSniper_Implementation();
    
    void OnSelectAction();
    void OffSelectAction();

    void BackQuitMenu_Back_Action();

public:
    FORCEINLINE class UCSelectActionWidget_Group* GetSelectActionWidget() { return SelectActionWidget; }



private:
    UPROPERTY()
        FInteractionData InteractionData;

    FORCEINLINE class UCInteractionComponent* GetInteractable() const { return InteractionData.ViewedInteractionComponent; }

protected:
    FTimerHandle TimerHandle_Interact;

public:
    bool IsInteracting() const;

    float GetRemainingInteractime() const;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Components")
        class UCInventoryComponent* PlayerInventory;

    // inventory에서 아이템을 사용할때
    UFUNCTION(BlueprintCallable, Category = "Items")
        void UseItem(class UCItem* Item);

    UFUNCTION(Reliable, Server)
        void ServerUseItem(class UCItem* Item);
    void ServerUseItem_Implementation(class UCItem* Item);

    // 아이템을 버릴때
    UFUNCTION(BlueprintCallable, Category = "Items")
        void DropItem(class UCItem* Item, const int32 Quantity);

    UFUNCTION(Reliable, Server, WithValidation)
        void ServerDropItem(class UCItem* Item, const int32 Quantity);
    void ServerDropItem_Implementation(class UCItem* Item, const int32 Quantity);
    bool ServerDropItem_Validate(class UCItem* Item, const int32 Quantity);

    // 블루프린트에서 사용
    UPROPERTY(EditDefaultsOnly, Category = "Item")
        TSubclassOf<class ACPickup> PickupClass;

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Animation")
        UAnimMontage* Climb;

private: // Axis
    void OnMoveForward(float Axis);
    void OnMoveRight(float Axis);

    void OnHorizontalLook(float Axis);
    void OnVerticalLook(float Axis);

private:    // Character Component
    UPROPERTY(VisibleDefaultsOnly)
        class UCStatusComponent* Status;

    UPROPERTY(VisibleDefaultsOnly)
        class UCStateComponent* State;

    UPROPERTY(VisibleDefaultsOnly)
        class UCMontagesComponent* Montages;

    UPROPERTY(VisibleDefaultsOnly)
        class UCActionComponent* Action;

private:
    UPROPERTY(VisibleDefaultsOnly)
        class USpringArmComponent* SpringArm;

protected:
    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
        class UCameraComponent* Camera;

    UPROPERTY(VisibleDefaultsOnly)
        class UCParkourSystem* parkour;

    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
        class USpringArmComponent* MinimapSpringArm;

    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
        class USceneCaptureComponent2D* RenderMinimap;

    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
        class UPaperSpriteComponent* Arrow;

    UPROPERTY(BlueprintReadOnly)
        class UCMainWidget* MainWidget;

private:
    TSubclassOf<class UCMainWidget> MainWidgetClass;

private:
    class UMaterialInstanceDynamic* Material_First;
    class UMaterialInstanceDynamic* Material_Second;

    bool bsword;
    bool bsniper;

public:     // Main Widget
    void SetMainWidget();
    virtual FGenericTeamId GetGenericTeamId() const override;

    UFUNCTION(BlueprintCallable)
        bool IsPlayerDead() { return playerDead; }
private:
    UPROPERTY(EditDefaultsOnly)
        uint8 PlayerTeamID = 0;
    FGenericTeamId TeamGeneicID;

    class ACharacter* Attacker;
    class AActor* Causer;
    float DamageValue;

    bool playerDead = false;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Widget")
        TSubclassOf<class UCPlayerHealthWidget> HealthWidgetClass;
    
    UPROPERTY(EditDefaultsOnly, Category = "Widget")
        TSubclassOf<class UCSelectActionWidget_Group> SelectActionWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "Menu")
        TSubclassOf<class UCBackQuitMenu> BackQuitMenuClass;


    class UCPlayerHealthWidget* HealthWidget;
    class UCSelectActionWidget_Group* SelectActionWidget;
    class UCBackQuitMenu* BackQuitMenu;
};