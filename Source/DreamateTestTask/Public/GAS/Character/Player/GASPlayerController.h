// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASMainCharacter.h"
#include "GenericTeamAgentInterface.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "DreamateTestTask/Public/UI/MainHUD.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "UI/InventoryWidget.h"
#include "GASPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API AGASPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	AGASPlayerController();
	
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

protected:

#pragma region CHARACTER_CAMERA

	UPROPERTY()
	UMovingCameraComponent* CameraComponent;
	UPROPERTY()
	URotatingSpringArmComponent* SpringArmComponent;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Camera")
	float CameraSpeed = 20.f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Camera")
	float CameraAngleSpeed = 1.0f;
	
	bool bIsCameraAttached = true;
	UPROPERTY()
	AGASMainCharacter* PlayerCharacter;

#pragma endregion
	
#pragma region INPUT
	
	// CONTROL INPUT ACTIONS //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
	UInputAction* IA_Movement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
	UInputAction* IA_CameraMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
	UInputAction* IA_AttachCamera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
    UInputAction* IA_RotateCamera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
	UInputAction* IA_Inventory;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
	UInputAction* IA_UseConsumable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
	UInputAction* IA_Interact;
	
	// CONTROL INPUT MAPPINGS //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Mappings")
	UInputMappingContext* ControlMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Mappings")
	int32 ControlsMappingPriority = 0;

	// COMBAT INPUT ACTIONS //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Combat|Input Actions")
	UInputAction* IA_Attack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Combat|Input Actions")
	UInputAction* IA_Roll;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Combat|Input Actions")
	UInputAction* IA_Parry;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Combat|Input Actions")
	UInputAction* IA_CastSpell;
	
	// COMBAT INPUT MAPPINGS //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Combat|Input Mappings")
	UInputMappingContext* CombatMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Combat|Input Mappings")
	int32 CombatMappingPriority = 1;

	// INPUT FUNCTIONS //
	void OnMovementAction();
	void OnCameraMovementAction(const FInputActionValue& Value);
	void OnAttachCameraAction();
	void OnDetachCameraAction();
	void OnRotateCameraAction(const FInputActionValue& Value);
	void OnAttackAction();
	void OnRollAction();
	void OnParryAction();
	void OnCastSpellAction();
	void OnUseConsumableAction();
	void OnInteractAction();

	UFUNCTION(BlueprintCallable)
	void OnInventoryAction();

#pragma endregion

#pragma region INVENTORY
	
	UPROPERTY(BlueprintReadOnly)
	UInventoryWidget* InventoryWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	UPROPERTY()
	bool bIsInventoryOpened = false;

#pragma endregion 

#pragma  region GENERICTEAMINTERFACE
	
	FGenericTeamId CharacterTeamID;

	virtual FGenericTeamId GetGenericTeamId() const override;

#pragma endregion

	bool bCanMove = true;
	
public:
	
	UInputMappingContext* GetControlMappingContext() const;
	int32 GetControlsMappingPriority() const;
	UInputMappingContext* GetCombatMappingContext() const;
	int32 GetCombatMappingPriority() const;
	void SetCanMove(bool bNewValue);
	
};

