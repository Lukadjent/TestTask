// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Character/Player/GASMainCharacter.h"

#include "GameModeInterface.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/Character/Player/GASPlayerController.h"
#include "Camera/MovingCameraComponent.h"
#include "Camera/RotatingSpringArmComponent.h"
#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"

AGASMainCharacter::AGASMainCharacter()
{
	
	SpringArmComponent = CreateDefaultSubobject<URotatingSpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	bUseControllerRotationYaw = true;
	SpringArmComponent->TargetArmLength = SpringArmLength;
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->SetRelativeRotation(FRotator(-60.f, -30.f, 0.f));

	CameraComponent = CreateDefaultSubobject<UMovingCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
}

void AGASMainCharacter::BeginPlay()
{
	Super::BeginPlay();
		
	IGameModeInterface* GameModeInterface = Cast<IGameModeInterface>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameModeInterface)
	{
		CharacterDeath.AddRaw(GameModeInterface, &IGameModeInterface::OnPlayerCharacterDeath);
	}
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("Status.LoseControl")),
													 EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AGASMainCharacter::LoseControlTagChanged);
	}
	InitializeDefaultAttributesAndEffects();
}

void AGASMainCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	if (const AGASPlayerController* PlayerController = Cast<AGASPlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(PlayerController->GetControlMappingContext(),
			                             PlayerController->GetControlsMappingPriority());
			Subsystem->AddMappingContext(PlayerController->GetCombatMappingContext(),
				                         PlayerController->GetCombatMappingPriority());
		}
	}
}

void AGASMainCharacter::ImmobileTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		GetMovementComponent()->StopMovementImmediately();
		GetMovementComponent()->Deactivate();
	}
	else
	{
		GetMovementComponent()->Activate();
	}
}

void AGASMainCharacter::LoseControlTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
	{
		return;
	}
	if (NewCount > 0)
	{
		PlayerController->StopMovement();
		DisableInput(PlayerController);
	}
	else
	{
		EnableInput(PlayerController);
	}
}

float AGASMainCharacter::GetHealth() const
{
	return AttributeSet->GetHealth();
}

float AGASMainCharacter::GetMaxHealth() const
{
	return AttributeSet->GetMaxHealth();
}

float AGASMainCharacter::GetMana() const
{
	return AttributeSet->GetMana();
}

float AGASMainCharacter::GetMaxMana() const
{
	return AttributeSet->GetMaxMana();
}

float AGASMainCharacter::GetStamina() const
{
	return AttributeSet->GetStamina();
}

float AGASMainCharacter::GetMaxStamina() const
{
	return AttributeSet->GetMaxStamina();
}

UMovingCameraComponent* AGASMainCharacter::GetMovingCameraComponent() const
{
	return CameraComponent;
}

URotatingSpringArmComponent* AGASMainCharacter::GetRotatingSpringArmComponent() const
{
	return SpringArmComponent;
}
