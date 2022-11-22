// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GASCharacterComponent.h"

#include "GameModeInterface.h"
#include "AsyncTask/AT_AttributeChange.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/Character.h"
#include "GAS/AbilitySystemComponentInterface.h"
#include "GAS/ASComponent.h"
#include "Interfaces/MovementComponentInterface.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UGASCharacterComponent::UGASCharacterComponent()
{
	
}


// Called when the game starts
void UGASCharacterComponent::BeginPlay()
{
	Super::BeginPlay();

	IGameModeInterface* GameModeInterface = Cast<IGameModeInterface>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameModeInterface)
	{
		GameModeInterface->CharacterSpawn(Cast<ACharacter>(GetOwner()));
	}

	IAbilitySystemComponentInterface* ASInterface = Cast<IAbilitySystemComponentInterface>(GetOwner());
	if (ASInterface)
	{
		ASInterface->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(ASInterface->GetAttributeSet()->GetMoveSpeedAttribute()).
								 AddUObject(this, &UGASCharacterComponent::OnMovementSpeedChange);
		ASInterface->GetAbilitySystemComponent()->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("Status.Immobile")),
													 EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UGASCharacterComponent::ImmobileTagChanged);
	}
}

void UGASCharacterComponent::OnMovementSpeedChange(const FOnAttributeChangeData& Data)
{
	const IMovementComponentInterface* MovementComponentInterface = Cast<IMovementComponentInterface>(GetOwner());
	if (MovementComponentInterface)
	{
		MovementComponentInterface->GetCharacterMovementComponent()->MaxWalkSpeed = Data.NewValue;
	}
}

void UGASCharacterComponent::ImmobileTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	const IMovementComponentInterface* MovementComponentInterface = Cast<IMovementComponentInterface>(GetOwner());
	if (MovementComponentInterface)
	{
		if (NewCount > 0)
		{
			MovementComponentInterface->GetCharacterMovementComponent()->StopMovementImmediately();
			MovementComponentInterface->GetCharacterMovementComponent()->Deactivate();
		}
		else
		{
			MovementComponentInterface->GetCharacterMovementComponent()->Activate();
		}
	}
}

