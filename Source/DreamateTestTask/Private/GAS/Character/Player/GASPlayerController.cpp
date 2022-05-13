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
#include "InteractableObjects/InteractableBase.h"
#include "Kismet/KismetMathLibrary.h"


void AGASPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Initialize MainCharacter and Components

	PlayerCharacter = Cast<AGASMainCharacter>(GetPawn());
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("AMainCharacterController: Failed To Initialize Player Character Controller!"));
	}
	CharacterCameraComponent = PlayerCharacter->CameraComponent;
	CharacterSpringArmComponent = PlayerCharacter->SpringArmComponent;
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
			EnhancedInputComponent->BindAction(IA_Movement, ETriggerEvent::Triggered, this,
											   &AGASPlayerController::CharacterMovement);
		}

		if (IA_CameraMovement)
		{
			EnhancedInputComponent->BindAction(IA_CameraMovement, ETriggerEvent::Started, this,
											   &AGASPlayerController::DetachCamera);
			EnhancedInputComponent->BindAction(IA_CameraMovement, ETriggerEvent::Triggered, this,
											   &AGASPlayerController::CameraMovement);
		}

		if (IA_AttachCamera)
		{
			EnhancedInputComponent->BindAction(IA_AttachCamera, ETriggerEvent::Started, this,
											   &AGASPlayerController::AttachCamera);
		}

		if (IA_RotateCamera) 
		{
			EnhancedInputComponent->BindAction(IA_RotateCamera, ETriggerEvent::Triggered, this,
											   &AGASPlayerController::RotateCamera);
		}

		if (IA_Attack) 
		{
			EnhancedInputComponent->BindAction(IA_Attack, ETriggerEvent::Started, this,
											   &AGASPlayerController::Attack);
		}

		if (IA_Roll)
		{
			EnhancedInputComponent->BindAction(IA_Roll, ETriggerEvent::Started, this, &AGASPlayerController::Roll);
		}

		if (IA_Parry)
		{
			EnhancedInputComponent->BindAction(IA_Parry, ETriggerEvent::Started, this, &AGASPlayerController::Parry);
		}

		if (IA_CastSpell)
		{
			EnhancedInputComponent->BindAction(IA_CastSpell, ETriggerEvent::Started, this, &AGASPlayerController::CastSpell);
		}
		
		if (IA_Inventory)
		{
			EnhancedInputComponent->BindAction(IA_Inventory, ETriggerEvent::Started, this, &AGASPlayerController::Inventory);
		}

		if (IA_UseConsumable)
		{
			EnhancedInputComponent->BindAction(IA_UseConsumable, ETriggerEvent::Started, this, &AGASPlayerController::UseConsumable);
		}

		if (IA_Interact)
		{
			EnhancedInputComponent->BindAction(IA_Interact, ETriggerEvent::Started, this, &AGASPlayerController::Interact);
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

void AGASPlayerController::CharacterMovement()
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

void AGASPlayerController::CameraMovement(const FInputActionValue& Value)
{

	//Calculate The Direction Of Camera Movement
	const float Angle = CharacterSpringArmComponent->GetRelativeRotation().Yaw;
	const FVector Direction (UKismetMathLibrary::GetRotated2D(FVector2d(Value[0], Value[1]), Angle), 0.f);

	//Calculate And Set New Location For Camera
	FVector Location = CharacterCameraComponent->GetRelativeLocation();
	//FVector Location = CharacterSpringArmComponent->GetRelativeLocation();
	Location += CameraSpeed * Direction;
	//CharacterSpringArmComponent->SetRelativeLocation(Location, true);
	CharacterCameraComponent->SetRelativeLocation(Location, true);
}

//Attach Camera Back To Spring Component

void AGASPlayerController::AttachCamera() 
{
	
	if (CharacterSpringArmComponent && !bIsCameraAttached)
	{
		CharacterCameraComponent->AttachToComponent(CharacterSpringArmComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
		//CharacterSpringArmComponent->AttachToComponent(MainCharacter->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
		bIsCameraAttached = true;
	}
}

//Detach Camera From Spring Component

void AGASPlayerController::DetachCamera() 
{
	if (bIsCameraAttached && CharacterSpringArmComponent && CharacterCameraComponent)
    {
		CharacterCameraComponent->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
		//CharacterSpringArmComponent->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
		bIsCameraAttached = false;
    }
}

// Rotate Camera Around Character

void AGASPlayerController::RotateCamera(const FInputActionValue& Value)
{
	if (bIsCameraAttached)
	{
		FRotator Rotation = CharacterSpringArmComponent->GetRelativeRotation();
		Rotation.Yaw -= Value[0] * CameraAngleSpeed;
		CharacterSpringArmComponent->SetRelativeRotation(Rotation);
	}
}

void AGASPlayerController::Attack()
{
	PlayerCharacter->Attack();
}

void AGASPlayerController::Roll()
{
	PlayerCharacter->Roll();
}

void AGASPlayerController::Parry()
{
	PlayerCharacter->Parry();
}

void AGASPlayerController::CastSpell()
{
	PlayerCharacter->CastSpell();
}

void AGASPlayerController::Inventory()
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

void AGASPlayerController::UseConsumable()
{
	PlayerCharacter->UseConsumable();
}

void AGASPlayerController::Interact()
{
	TArray<AActor*> OverlappingActors;
	TSubclassOf<AInteractableBase> ClassFilter;
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
