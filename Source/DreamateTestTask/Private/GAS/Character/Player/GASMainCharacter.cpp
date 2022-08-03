// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Character/Player/GASMainCharacter.h"

#include "CharacterDeathHandleInterface.h"
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
		
	ICharacterDeathHandleInterface* CharacterDeathHandleInterface = Cast<ICharacterDeathHandleInterface>(UGameplayStatics::GetGameMode(GetWorld()));
	if (CharacterDeathHandleInterface)
	{
		CharacterDeath.AddRaw(CharacterDeathHandleInterface, &ICharacterDeathHandleInterface::OnPlayerCharacterDeath);
	}
	
	if (AbilitySystemComponent)
	{
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &AGASMainCharacter::MaxHealthChanged);
		MaxManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxManaAttribute()).AddUObject(this, &AGASMainCharacter::MaxManaChanged);
		MaxStaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &AGASMainCharacter::MaxStaminaChanged);
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
	if (AGASPlayerController* PlayerController = Cast<AGASPlayerController>(GetController()))
	{
		const bool bCanMove = NewCount > 0 ? false : true;
		PlayerController->SetCanMove(bCanMove);
		if (!bCanMove)
		{
			GetMovementComponent()->StopMovementImmediately();
		}
	}
}

void AGASMainCharacter::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	float MaxHealth = Data.NewValue;
	if (AGASPlayerController* PlayerController = Cast<AGASPlayerController>(GetController()))
	{
		if (AMainHUD* HUD = Cast<AMainHUD>(PlayerController->GetHUD()))
		{
			HUD->MainHUDWidget->SetMaxHealth(MaxHealth);
		}
	}
}

void AGASMainCharacter::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	float MaxMana = Data.NewValue;
	if (AGASPlayerController* PlayerController = Cast<AGASPlayerController>(GetController()))
	{
		if (AMainHUD* HUD = Cast<AMainHUD>(PlayerController->GetHUD()))
		{
			HUD->MainHUDWidget->SetMaxMana(MaxMana);
		}
	}	
}

void AGASMainCharacter::MaxStaminaChanged(const FOnAttributeChangeData& Data)
{
	float MaxStamina = Data.NewValue;
	if (AGASPlayerController* PlayerController = Cast<AGASPlayerController>(GetController()))
	{
		if (AMainHUD* HUD = Cast<AMainHUD>(PlayerController->GetHUD()))
		{
			HUD->MainHUDWidget->SetMaxStamina(MaxStamina);
		}
	}
}

void AGASMainCharacter::StaminaRegenRateChanged(const FOnAttributeChangeData& Data)
{
	float StaminaRegenRate = Data.NewValue;
	if (AGASPlayerController* PlayerController = Cast<AGASPlayerController>(GetController()))
	{
		if (AMainHUD* HUD = Cast<AMainHUD>(PlayerController->GetHUD()))
		{
			HUD->MainHUDWidget->SetStaminaRegenRate(StaminaRegenRate);
		}
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
