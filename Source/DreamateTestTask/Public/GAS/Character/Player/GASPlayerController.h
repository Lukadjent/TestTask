// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASMainCharacter.h"
#include "GenericTeamAgentInterface.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "PlayerControllerInterface.h"
#include "DreamateTestTask/Public/UI/MainHUD.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/InputMappingInterface.h"
#include "UI/InventoryWidget.h"
#include "GASPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API AGASPlayerController : public APlayerController, public IGenericTeamAgentInterface, public IPlayerControllerInterface, public IInputMappingInterface
{
	GENERATED_BODY()

	AGASPlayerController();
	
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

protected:

#pragma region CHARACTER_COMPONENTS

	UPROPERTY()
	TSoftObjectPtr<UMovingCameraComponent> CameraComponent;

	UPROPERTY()
	TSoftObjectPtr<URotatingSpringArmComponent> SpringArmComponent;

	TSoftObjectPtr<UInteractionComponent> InteractionComponent;

#pragma endregion
	
#pragma region INPUT
	
	// CONTROL INPUT ACTIONS //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
	TSoftObjectPtr<UInputAction> IA_Movement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
	TSoftObjectPtr<UInputAction> IA_CameraMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
	TSoftObjectPtr<UInputAction> IA_AttachCamera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
    TSoftObjectPtr<UInputAction> IA_RotateCamera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
	TSoftObjectPtr<UInputAction> IA_Inventory;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
	TSoftObjectPtr<UInputAction> IA_Interact;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Combat|Input Mappings")
	TMap<UInputMappingContext*, int32> MappingContexts;

	// INPUT FUNCTIONS //
	void OnMovementAction();
	void OnCameraMovementAction(const FInputActionValue& Value);
	void OnAttachCameraAction();
	void OnDetachCameraAction();
	void OnRotateCameraAction(const FInputActionValue& Value);
	void OnInteractAction();

	UFUNCTION(BlueprintCallable)
	void OnInventoryAction();

#pragma endregion

#pragma  region GENERICTEAMINTERFACE
	
	FGenericTeamId CharacterTeamID;

	virtual FGenericTeamId GetGenericTeamId() const override;

#pragma endregion

public:
	
	virtual TMap<UInputMappingContext*, int32> GetInputContextsMap() const override;
};

