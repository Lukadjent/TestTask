// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Character/Player/GASPlayerController.h"
#include "EnhancedInputComponent.h"
#include "NetworkMessage.h"
#include "ParticleHelper.h"
#include "DreamateTestTask/Public/GAS/Character/AI/GASBaseCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "VectorTypes.h"
#include "Camera/MovingCameraComponent.h"
#include "GAS/AbilitySystemComponentInterface.h"
#include "InteractableObjects/InteractionInterface.h"
#include "Inventory/InventoryComponent.h"
#include "Kismet/KismetMathLibrary.h"

void AGASPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Initialize MainCharacter and Components
	const ICameraInterface* Camera = Cast<ICameraInterface>(GetPawn());
	if (!Camera)
	{
		UE_LOG(LogTemp, Error, TEXT("AMainCharacterController: Failed To Initialize CAMERA in GASPlayerCharacterController!"));
		return;
	}
	const IInteractionComponentInterface* Interaction = Cast<IInteractionComponentInterface>(GetPawn());
	if (!Interaction)
	{
		UE_LOG(LogTemp, Error, TEXT("AMainCharacterController: Failed To Initialize ABILITY SYSTEM COMPONENT in GASPlayerCharacterController!"));
		return;
	}
	CameraComponent = Camera->GetMovingCameraComponent();
	SpringArmComponent = Camera->GetRotatingSpringArmComponent();
	InteractionComponent = Interaction->GetInteractionComponent();
}

AGASPlayerController::AGASPlayerController()
{
	CharacterTeamID = FGenericTeamId(0);

	//Enabling Mouse Events

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AGASPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	//Binding Input Actions To Functions

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (IA_Movement)
		{
			EnhancedInputComponent->BindAction(IA_Movement.Get(), ETriggerEvent::Triggered, this,
											   &AGASPlayerController::OnMovementAction);
		}

		if (IA_CameraMovement)
		{
			EnhancedInputComponent->BindAction(IA_CameraMovement.Get(), ETriggerEvent::Started, this,
											   &AGASPlayerController::OnDetachCameraAction);
			EnhancedInputComponent->BindAction(IA_CameraMovement.Get(), ETriggerEvent::Triggered, this,
											   &AGASPlayerController::OnCameraMovementAction);
		}

		if (IA_AttachCamera)
		{
			EnhancedInputComponent->BindAction(IA_AttachCamera.Get(), ETriggerEvent::Triggered, this,
											   &AGASPlayerController::OnAttachCameraAction);
		}

		if (IA_RotateCamera) 
		{
			EnhancedInputComponent->BindAction(IA_RotateCamera.Get(), ETriggerEvent::Started, this,
												   &AGASPlayerController::OnAttachCameraAction);
			EnhancedInputComponent->BindAction(IA_RotateCamera.Get(), ETriggerEvent::Triggered, this,
											   &AGASPlayerController::OnRotateCameraAction);
		}
		
		if (IA_Inventory)
		{
			EnhancedInputComponent->BindAction(IA_Inventory.Get(), ETriggerEvent::Started, this, &AGASPlayerController::OnInventoryAction);
		}

		if (IA_Interact)
		{
			EnhancedInputComponent->BindAction(IA_Interact.Get(), ETriggerEvent::Started, this, &AGASPlayerController::OnInteractAction);
		}
	}
}

TMap<UInputMappingContext*, int32> AGASPlayerController::GetInputContextsMap() const
{
	return MappingContexts;
}

void AGASPlayerController::OnMovementAction()
{
	//Finding A Point For Character To Go
	FHitResult Result;
	GetHitResultUnderCursor(ECC_Visibility, true, Result);

	//Character Moves To Location
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Result.Location);
}

void AGASPlayerController::OnCameraMovementAction(const FInputActionValue& Value)
{
	CameraComponent->MoveCamera(Value);
}

//Attach Camera Back To Spring Component

void AGASPlayerController::OnAttachCameraAction() 
{
	CameraComponent->AttachCameraToComponent(SpringArmComponent.Get());
}

//Detach Camera From Spring Component

void AGASPlayerController::OnDetachCameraAction() 
{
	CameraComponent->DetachCameraFromParent();
}

// Rotate Camera Around Character

void AGASPlayerController::OnRotateCameraAction(const FInputActionValue& Value)
{
	SpringArmComponent->RotateCamera(Value);
}

void AGASPlayerController::OnInventoryAction()
{
	OpenInventoryActionDelegate.Broadcast();
}

void AGASPlayerController::OnInteractAction()
{
	InteractionComponent->Interact();
}

FGenericTeamId AGASPlayerController::GetGenericTeamId() const
{
	return CharacterTeamID;
}
