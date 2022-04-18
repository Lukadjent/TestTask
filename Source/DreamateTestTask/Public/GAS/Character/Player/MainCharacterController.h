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
#include "MainCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API AMainCharacterController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	AMainCharacterController();
	
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

public:

	

#pragma region CHARACTERCAMERA

	UPROPERTY()
	UCameraComponent* CharacterCameraComponent;
	UPROPERTY()
	USpringArmComponent* CharacterSpringArmComponent;
	float CameraSpeed = 20.f;
	float CameraAngleSpeed = 1.0f;
	bool bIsCameraAttached = true;
	UPROPERTY()
	AGASMainCharacter* MainCharacter;

#pragma endregion
	
#pragma region INPUT
	
	// CONTROL INPUT ACTIONS //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
	UInputAction* MovementAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
	UInputAction* CameraMovementAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
	UInputAction* CameraAttachAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
    UInputAction* CameraRotationAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
	UInputAction* InventoryAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Actions")
	UInputAction* UseConsumableAction;
	
	// CONTROL INPUT MAPPINGS //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Mappings")
	UInputMappingContext* ControlMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Control|Input Mappings")
	int32 ControlsMappingPriority = 0;

	// COMBAT INPUT ACTIONS //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Combat|Input Actions")
	UInputAction* AttackAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Combat|Input Actions")
	UInputAction* RollAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Combat|Input Actions")
	UInputAction* ParryAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Combat|Input Actions")
	UInputAction* CastSpellAction;
	
	// COMBAT INPUT MAPPINGS //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Combat|Input Mappings")
	UInputMappingContext* CombatMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Combat|Input Mappings")
	int32 CombatMappingPriority = 1;

	// INPUT FUNCTIONS //
	void EnhancedCharacterMovement();
	void EnhancedCameraMovement(const FInputActionValue& Value);
	void AttachCameraToCharacter();
	void DetachCameraFromCharacter();
	void RotateCamera(const FInputActionValue& Value);
	void Attack();
	void Roll();
	void Parry();
	void CastSpell();
	void Inventory();
	void UseConsumable();
	
#pragma endregion

#pragma region INVENTORY
	
	UPROPERTY(BlueprintReadOnly)
	UInventoryWidget* InventoryWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<UUserWidget> InventoryWidgetClass;
	UPROPERTY()
	bool bIsOpened = false;

#pragma endregion 

private:

#pragma  region GENERICTEAMINTERFACE
	
	FGenericTeamId CharacterTeamID;

	virtual FGenericTeamId GetGenericTeamId() const override;

#pragma endregion
	
};

