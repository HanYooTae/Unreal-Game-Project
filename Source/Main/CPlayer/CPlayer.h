#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class MAIN_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

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

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USpringArmComponent* MinimapSpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USceneCaptureComponent2D* RenderMinimap;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UPaperSpriteComponent* Arrow;

private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

// Main Widget
public:
	void SetMainWidget();

private:
	class UCMainWidget* MainWidget;
	TSubclassOf<class UCMainWidget> MainWidgetClass;
};
