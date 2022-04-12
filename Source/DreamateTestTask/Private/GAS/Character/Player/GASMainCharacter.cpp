// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Character/Player/GASMainCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/Character/Player/MainCharacterController.h"

AGASMainCharacter::AGASMainCharacter()
{
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	bUseControllerRotationYaw = true;
	SpringArmComponent->TargetArmLength = SpringArmLength;
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->SetRelativeRotation(FRotator(-60.f, -30.f, 0.f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	
	
}

void AGASMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystemComponent)
	{
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &AGASMainCharacter::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &AGASMainCharacter::MaxHealthChanged);
		//HealthRegenRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthRegenRateAttribute()).AddUObject(this, &AGASMainCharacter::HealthRegenRateChanged);
		//ManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetManaAttribute()).AddUObject(this, &AGASMainCharacter::ManaChanged);
		MaxManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxManaAttribute()).AddUObject(this, &AGASMainCharacter::MaxManaChanged);
		//ManaRegenRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetManaRegenRateAttribute()).AddUObject(this, &AGASMainCharacter::ManaRegenRateChanged);
		//StaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetStaminaAttribute()).AddUObject(this, &AGASMainCharacter::StaminaChanged);
		MaxStaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &AGASMainCharacter::MaxStaminaChanged);
		//StaminaRegenRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetStaminaRegenRateAttribute()).AddUObject(this, &AGASMainCharacter::StaminaRegenRateChanged);
	}
	
	InitializeDefaultAttributesAndEffects();
}

void AGASMainCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	if (const AMainCharacterController* PlayerController = Cast<AMainCharacterController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(PlayerController->ControlMappingContext,
			                             PlayerController->ControlsMappingPriority);
			Subsystem->AddMappingContext(PlayerController->CombatMappingContext,
				                         PlayerController->CombatMappingPriority);
		}
	}
}

void AGASMainCharacter::Roll()
{
	AbilitySystemComponent->TryActivateAbilityByClass(StandardAbilities[EAbilities::Roll]);
}

void AGASMainCharacter::Parry()
{
	AbilitySystemComponent->TryActivateAbilityByClass(StandardAbilities[EAbilities::Parry]);
}

void AGASMainCharacter::CastSpell()
{
	AbilitySystemComponent->TryActivateAbilityByClass(StandardAbilities[EAbilities::CastSpell]);
}

void AGASMainCharacter::HealthChanged(const FOnAttributeChangeData& Data)
{
	
}

void AGASMainCharacter::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	float MaxHealth = Data.NewValue;
	if (AMainCharacterController* PlayerController = Cast<AMainCharacterController>(GetController()))
	{
		if (AMainHUD* HUD = Cast<AMainHUD>(PlayerController->GetHUD()))
		{
			HUD->MainHUDWidget->SetMaxHealth(MaxHealth);
		}
	}
}

void AGASMainCharacter::HealthRegenRateChanged(const FOnAttributeChangeData& Data)
{
	float HealthRegenRate = Data.NewValue;
	if (AMainCharacterController* PlayerController = Cast<AMainCharacterController>(GetController()))
	{
		if (AMainHUD* HUD = Cast<AMainHUD>(PlayerController->GetHUD()))
		{
			HUD->MainHUDWidget->SetHealthRegenRate(HealthRegenRate);
		}
	}
}

void AGASMainCharacter::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	float MaxMana = Data.NewValue;
	if (AMainCharacterController* PlayerController = Cast<AMainCharacterController>(GetController()))
	{
		if (AMainHUD* HUD = Cast<AMainHUD>(PlayerController->GetHUD()))
		{
			HUD->MainHUDWidget->SetMaxMana(MaxMana);
		}
	}	
}

void AGASMainCharacter::ManaRegenRateChanged(const FOnAttributeChangeData& Data)
{
	float ManaRegenRate = Data.NewValue;
	if (AMainCharacterController* PlayerController = Cast<AMainCharacterController>(GetController()))
	{
		if (AMainHUD* HUD = Cast<AMainHUD>(PlayerController->GetHUD()))
		{
			HUD->MainHUDWidget->SetManaRegenRate(ManaRegenRate);
		}
	}
}

void AGASMainCharacter::MaxStaminaChanged(const FOnAttributeChangeData& Data)
{
	float MaxStamina = Data.NewValue;
	if (AMainCharacterController* PlayerController = Cast<AMainCharacterController>(GetController()))
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
	if (AMainCharacterController* PlayerController = Cast<AMainCharacterController>(GetController()))
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


