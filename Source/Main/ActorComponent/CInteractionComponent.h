#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "CInteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginInteract, class ACPlayer*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndInteract, class ACPlayer*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginFocus, class ACPlayer*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndFocus, class ACPlayer*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, class ACPlayer*, Character);

UCLASS(ClassGroup = "Custom", meta = (BlueprintSpawnableComponent))
class MAIN_API UCInteractionComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

	UCInteractionComponent();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Interaction")
		float InteractionTime;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Interaction")
		float InteractionDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Interaction")
		FText InteractableNameText;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Interaction")
		FText InteractableActionText;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Interaction")
		bool bAllowMultipleInteractors;

	//Delegates
	//[Local + server] 플레이어가 이 상호작용 가능한 액터에 초점을 맞추는 동안 상호작용 키를 누를 때 호출됩니다.
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
		FOnBeginInteract OnBeginInteract;

	//[Local + server] 플레이어가 상호작용 키를 놓을 때, 상호작용 가능한 액터를 보는 것을 멈추거나 상호작용을 시작한 후 너무 멀리 갈 때 호출됩니다.
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
		FOnEndInteract OnEndInteract;

	//[Local + server] 플레이어가 이 상호작용 가능한 액터에 초점을 맞추는 동안 상호작용 키를 누를 때 호출됩니다.
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
		FOnBeginFocus OnBeginFocus;

	//[Local + server] 플레이어가 상호작용 키를 놓으면 호출됩니다.상호작용 가능한 액터를 보는 것을 멈추거나 상호작용을 시작한 후 너무 멀리 떨어져 있을때
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
		FOnEndFocus OnEndFocus;

	//[Local + server] 아이템과 상호작용할 때 호출됩니다.(플레이어가 필요한 양의 아이템에 관하여)
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
		FOnBeginInteract OnInteract;

public:
	// 플레이어 상호 작용 확인 추적이 이 Client에 대한 타격을 시작/종료할 때 클라이언트에서 호출됩니다.
	void BeginFocus(class ACPlayer* Character);
	void EndFocus(class ACPlayer* Character);

	// 플레이어가 Client와의 상호 작용을 시작 / 종료할 때 클라이언트에서 호출됩니다.
	void BeginInteract(class ACPlayer* Character);
	void EndInteract(class ACPlayer* Character);

	void Interact(class ACPlayer* Character);
			
};
