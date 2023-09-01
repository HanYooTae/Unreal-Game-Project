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
	//[Local + server] �÷��̾ �� ��ȣ�ۿ� ������ ���Ϳ� ������ ���ߴ� ���� ��ȣ�ۿ� Ű�� ���� �� ȣ��˴ϴ�.
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
		FOnBeginInteract OnBeginInteract;

	//[Local + server] �÷��̾ ��ȣ�ۿ� Ű�� ���� ��, ��ȣ�ۿ� ������ ���͸� ���� ���� ���߰ų� ��ȣ�ۿ��� ������ �� �ʹ� �ָ� �� �� ȣ��˴ϴ�.
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
		FOnEndInteract OnEndInteract;

	//[Local + server] �÷��̾ �� ��ȣ�ۿ� ������ ���Ϳ� ������ ���ߴ� ���� ��ȣ�ۿ� Ű�� ���� �� ȣ��˴ϴ�.
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
		FOnBeginFocus OnBeginFocus;

	//[Local + server] �÷��̾ ��ȣ�ۿ� Ű�� ������ ȣ��˴ϴ�.��ȣ�ۿ� ������ ���͸� ���� ���� ���߰ų� ��ȣ�ۿ��� ������ �� �ʹ� �ָ� ������ ������
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
		FOnEndFocus OnEndFocus;

	//[Local + server] �����۰� ��ȣ�ۿ��� �� ȣ��˴ϴ�.(�÷��̾ �ʿ��� ���� �����ۿ� ���Ͽ�)
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
		FOnBeginInteract OnInteract;

public:
	// �÷��̾� ��ȣ �ۿ� Ȯ�� ������ �� Client�� ���� Ÿ���� ����/������ �� Ŭ���̾�Ʈ���� ȣ��˴ϴ�.
	void BeginFocus(class ACPlayer* Character);
	void EndFocus(class ACPlayer* Character);

	// �÷��̾ Client���� ��ȣ �ۿ��� ���� / ������ �� Ŭ���̾�Ʈ���� ȣ��˴ϴ�.
	void BeginInteract(class ACPlayer* Character);
	void EndInteract(class ACPlayer* Character);

	void Interact(class ACPlayer* Character);
			
};
