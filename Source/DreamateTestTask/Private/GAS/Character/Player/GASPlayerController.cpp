// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Character/Player/GASPlayerController.h"
#include "EnhancedInputComponent.h"
#include "NetworkMessage.h"
#include "DreamateTestTask/Public/GAS/Character/AI/GASBaseCharacter.h"
#include "DreamateTestTask/Public/GAS/Character/Player/GASMainCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "VectorTypes.h"
#include "Camera/MovingCameraComponent.h"
#include "InteractableObjects/InteractableBase.h"
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
	CameraComponent = Camera->GetMovingCameraComponent();
	SpringArmComponent = Camera->GetRotatingSpringArmComponent();
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
	
	UMovingCameraComponent* Camera = CameraComponent;
	

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{

		if (IA_Movement)
		{
			EnhancedInputComponent->BindAction(IA_Movement, ETriggerEvent::Triggered, this,
											   &AGASPlayerController::OnMovementAction);//OnMovementAction
		}

		if (IA_CameraMovement)
		{
			EnhancedInputComponent->BindAction(IA_CameraMovement, ETriggerEvent::Started, this,
											   &AGASPlayerController::OnDetachCameraAction);
			EnhancedInputComponent->BindAction(IA_CameraMovement, ETriggerEvent::Triggered, this,
											   &AGASPlayerController::OnCameraMovementAction);
		}

		if (IA_AttachCamera)
		{
			EnhancedInputComponent->BindAction(IA_AttachCamera, ETriggerEvent::Triggered, this,
											   &AGASPlayerController::OnAttachCameraAction);
		}

		if (IA_RotateCamera) 
		{
			EnhancedInputComponent->BindAction(IA_RotateCamera, ETriggerEvent::Started, this,
												   &AGASPlayerController::OnAttachCameraAction);
			EnhancedInputComponent->BindAction(IA_RotateCamera, ETriggerEvent::Triggered, this,
											   &AGASPlayerController::OnRotateCameraAction);
		}

		if (IA_Attack) 
		{
			EnhancedInputComponent->BindAction(IA_Attack, ETriggerEvent::Started, this,
											   &AGASPlayerController::OnAttackAction);
		}

		if (IA_Roll)
		{
			EnhancedInputComponent->BindAction(IA_Roll, ETriggerEvent::Started, this, &AGASPlayerController::OnRollAction);
		}

		if (IA_Parry)
		{
			EnhancedInputComponent->BindAction(IA_Parry, ETriggerEvent::Started, this, &AGASPlayerController::OnParryAction);
		}

		if (IA_CastSpell)
		{
			EnhancedInputComponent->BindAction(IA_CastSpell, ETriggerEvent::Started, this, &AGASPlayerController::OnCastSpellAction);
		}
		
		if (IA_Inventory)
		{
			EnhancedInputComponent->BindAction(IA_Inventory, ETriggerEvent::Started, this, &AGASPlayerController::OnInventoryAction);
		}

		if (IA_UseConsumable)
		{
			EnhancedInputComponent->BindAction(IA_UseConsumable, ETriggerEvent::Started, this, &AGASPlayerController::OnUseConsumableAction);
		}

		if (IA_Interact)
		{
			EnhancedInputComponent->BindAction(IA_Interact, ETriggerEvent::Started, this, &AGASPlayerController::OnInteractAction);
		}
	}
}

UInputMappingContext* AGASPlayerController::GetControlMappingContext() const
{
	return ControlMappingContext;
}

int32 AGASPlayerController::GetControlsMappingPriority() const
{
	return ControlsMappingPriority;
}

UInputMappingContext* AGASPlayerController::GetCombatMappingContext() const
{
	return CombatMappingContext;
}

int32 AGASPlayerController::GetCombatMappingPriority() const
{
	return CombatMappingPriority;
}

void AGASPlayerController::SetCanMove(bool bNewValue)
{
	bCanMove = bNewValue;
}

void AGASPlayerController::OnMovementAction()
{
	if (bCanMove)
	{
		//Finding A Point For Character To Go
		FHitResult Result;
		GetHitResultUnderCursor(ECC_Visibility, true, Result);

		//Character Moves To Location
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Result.Location);
	}
}

void AGASPlayerController::OnCameraMovementAction(const FInputActionValue& Value)
{
	CameraComponent->MoveCamera(Value);
}

//Attach Camera Back To Spring Component

void AGASPlayerController::OnAttachCameraAction() 
{
	CameraComponent->AttachCameraToComponent(SpringArmComponent);
}

//Detach Camera From Spring Component

void AGASPlayerController::OnDetachCameraAction() 
{
	CameraComponent->DetachCameraFromParent();
}

// Rotate Camera Around Character

void AGASPlayerController::OnRotateCameraAction(const FInputActionValue& Value)
{
	if (CameraComponent->IsAttachedTo(SpringArmComponent))
	{
		SpringArmComponent->RotateCamera(Value);
	}
}

void AGASPlayerController::OnAttackAction()
{
	PlayerCharacter->Attack();
}

void AGASPlayerController::OnRollAction()
{
	PlayerCharacter->Roll();
}

void AGASPlayerController::OnParryAction()
{
	PlayerCharacter->Parry();
}

void AGASPlayerController::OnCastSpellAction()
{
	PlayerCharacter->CastSpell();
}

void AGASPlayerController::OnInventoryAction()
{
	if (!bIsInventoryOpened)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
		if (InventoryWidget)
		{
			InventoryWidget->AddToViewport();
		}
	}
	else
	{
		InventoryWidget->RemoveFromViewport();
	}
	bIsInventoryOpened = !bIsInventoryOpened;
}

void AGASPlayerController::OnUseConsumableAction()
{
	PlayerCharacter->UseConsumable();
}

void AGASPlayerController::OnInteractAction()
{
	TArray<AActor*> OverlappingActors;
	const TSubclassOf<AInteractableBase> ClassFilter;
	PlayerCharacter->GetOverlappingActors(OverlappingActors, ClassFilter);
	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (AInteractableBase* Interactable = Cast<AInteractableBase>(OverlappingActor))
		{
			Interactable->OnInteraction(PlayerCharacter);
			break;
		}
	}
}

FGenericTeamId AGASPlayerController::GetGenericTeamId() const
{
	return CharacterTeamID;
}
