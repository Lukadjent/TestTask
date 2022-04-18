// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Character/Player/MainCharacterController.h"
#include "EnhancedInputComponent.h"
#include "DreamateTestTask/Public/GAS/Character/AI/GASBaseCharacter.h"
#include "DreamateTestTask/Public/GAS/Character/Player/GASMainCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "VectorTypes.h"
#include "Kismet/KismetMathLibrary.h"


void AMainCharacterController::BeginPlay()
{
	Super::BeginPlay();

	//Initialize MainCharacter and Components

	MainCharacter = Cast<AGASMainCharacter>(GetPawn());
	if (MainCharacter)
	{
		CharacterCameraComponent = MainCharacter->CameraComponent;
		CharacterSpringArmComponent = MainCharacter->SpringArmComponent;
	}
}

AMainCharacterController::AMainCharacterController()
{
	CharacterTeamID = FGenericTeamId(0);

	//Enabling Mouse Events

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AMainCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	//Binding Input Actions To Functions

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{

		if (MovementAction)
		{
			EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this,
											   &AMainCharacterController::EnhancedCharacterMovement);
		}

		if (CameraMovementAction)
		{
			EnhancedInputComponent->BindAction(CameraMovementAction, ETriggerEvent::Started, this,
											   &AMainCharacterController::DetachCameraFromCharacter);
			EnhancedInputComponent->BindAction(CameraMovementAction, ETriggerEvent::Triggered, this,
											   &AMainCharacterController::EnhancedCameraMovement);
		}

		if (CameraAttachAction)
		{
			EnhancedInputComponent->BindAction(CameraAttachAction, ETriggerEvent::Started, this,
											   &AMainCharacterController::AttachCameraToCharacter);
		}

		if (CameraRotationAction) 
		{
			EnhancedInputComponent->BindAction(CameraRotationAction, ETriggerEvent::Triggered, this,
											   &AMainCharacterController::RotateCamera);
		}

		if (AttackAction) 
		{
			EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this,
											   &AMainCharacterController::Attack);
		}

		if (RollAction)
		{
			EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Started, this, &AMainCharacterController::Roll);
		}

		if (ParryAction)
		{
			EnhancedInputComponent->BindAction(ParryAction, ETriggerEvent::Started, this, &AMainCharacterController::Parry);
		}

		if (CastSpellAction)
		{
			EnhancedInputComponent->BindAction(CastSpellAction, ETriggerEvent::Started, this, &AMainCharacterController::CastSpell);
		}
		if (InventoryAction)
		{
			EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AMainCharacterController::Inventory);
		}
		if (UseConsumableAction)
		{
			EnhancedInputComponent->BindAction(UseConsumableAction, ETriggerEvent::Started, this, &AMainCharacterController::UseConsumable);
		}
	}
}

void AMainCharacterController::EnhancedCharacterMovement()
{
	
	//Finding A Point For Character To Go

	FHitResult Result;
	GetHitResultUnderCursor(ECC_Visibility, true, Result);

	//Character Moves To Location

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Result.Location);
}

void AMainCharacterController::EnhancedCameraMovement(const FInputActionValue& Value)
{

	//Calculate The Direction Of Camera Movement
	
	const float Angle = CharacterSpringArmComponent->GetRelativeRotation().Yaw;
	const FVector Direction (UKismetMathLibrary::GetRotated2D(FVector2d(Value[0], Value[1]), Angle), 0.f);

	//Calculate And Set New Location For Camera
	FVector Location = CharacterCameraComponent->GetRelativeLocation();
	Location += CameraSpeed * Direction;
	CharacterCameraComponent->SetRelativeLocation(Location);
}

//Attach Camera Back To Spring Component

void AMainCharacterController::AttachCameraToCharacter() 
{
	
	if (CharacterCameraComponent && CharacterSpringArmComponent && !bIsCameraAttached)
	{
		CharacterCameraComponent->AttachToComponent(CharacterSpringArmComponent,FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
		bIsCameraAttached = true;
	}
}

//Detach Camera From Spring Component

void AMainCharacterController::DetachCameraFromCharacter() 
{
	
	if (CharacterCameraComponent && bIsCameraAttached)
    {
    	CharacterCameraComponent->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
		bIsCameraAttached = false;
    }
}

// Rotate Camera Around Character

void AMainCharacterController::RotateCamera(const FInputActionValue& Value)
{
	
	if (bIsCameraAttached)
	{
		FRotator Rotation = CharacterSpringArmComponent->GetRelativeRotation();
		Rotation.Yaw -= Value[0] * CameraAngleSpeed;
		CharacterSpringArmComponent->SetRelativeRotation(Rotation);
	}
}

void AMainCharacterController::Attack()
{
	MainCharacter->Attack();
}

void AMainCharacterController::Roll()
{
	MainCharacter->Roll();
}

void AMainCharacterController::Parry()
{
	MainCharacter->Parry();
}

void AMainCharacterController::CastSpell()
{
	MainCharacter->CastSpell();
}

void AMainCharacterController::Inventory()
{
	InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
	if (InventoryWidget)
	{
		InventoryWidget->AddToViewport();
	}
}

void AMainCharacterController::UseConsumable()
{
	MainCharacter->UseConsumable();
}

FGenericTeamId AMainCharacterController::GetGenericTeamId() const
{
	return CharacterTeamID;
}
