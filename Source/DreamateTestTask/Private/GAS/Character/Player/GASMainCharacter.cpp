// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Character/Player/GASMainCharacter.h"

#include "GameModeInterface.h"
#include "EnhancedInputSubsystems.h"
#include "GAS/Character/Player/GASPlayerController.h"
#include "Camera/MovingCameraComponent.h"
#include "Camera/RotatingSpringArmComponent.h"
#include "GameFramework/GameMode.h"
#include "GAS/Ability/AbilitySet.h"
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

	AbilityBindingInputComponent = CreateDefaultSubobject<UAbilityBindingInputComponent>("AbilityBinding");

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");

	EnhancedInputComponent = CreateDefaultSubobject<UEnhancedInputComponent>("Enhanced");

	AbilitySetComponent = CreateDefaultSubobject<UAbilitySetComponent>("AbilitySetComponent");

	InputComponent = EnhancedInputComponent;

	GASCharacterComponent = CreateDefaultSubobject<UGASCharacterComponent>("GASCharacterComponent");
}

void AGASMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("Status.LoseControl")),
													 EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AGASMainCharacter::LoseControlTagChanged);
	}
}

void AGASMainCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
	
	const IInputMappingInterface* InputMappingInterface = Cast<IInputMappingInterface>(GetController());
	const APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (InputMappingInterface && PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			for (const TTuple<UInputMappingContext*, int32>& Context : InputMappingInterface->GetInputContextsMap())
			{
				Subsystem->AddMappingContext(Context.Key, Context.Value);
			}
		}
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

UMovingCameraComponent* AGASMainCharacter::GetMovingCameraComponent() const
{
	return CameraComponent;
}

URotatingSpringArmComponent* AGASMainCharacter::GetRotatingSpringArmComponent() const
{
	return SpringArmComponent;
}

void AGASMainCharacter::BindAbility(FGameplayAbilitySpec& Spec) const
{
	if (AbilitySetComponent->GetAbilitySet())
	{
		AbilitySetComponent->GetAbilitySet()->BindAbility(AbilityBindingInputComponent,Spec);
	}
}

void AGASMainCharacter::UnbindAbility(FGameplayAbilitySpec& Spec) const
{
	if (AbilitySetComponent->GetAbilitySet())
	{
		AbilitySetComponent->GetAbilitySet()->UnbindAbility(AbilityBindingInputComponent,Spec);
	}
}

UInteractionComponent* AGASMainCharacter::GetInteractionComponent() const
{
	return InteractionComponent;
}
