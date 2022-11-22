// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AbilitySetComponent.h"

#include "GAS/AbilitySystemComponentInterface.h"
#include "GAS/Ability/AbilitySet.h"


// Sets default values for this component's properties
UAbilitySetComponent::UAbilitySetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbilitySetComponent::BeginPlay()
{
	Super::BeginPlay();

	const IAbilitySystemComponentInterface* ASInterface = Cast<IAbilitySystemComponentInterface>(GetOwner());
	if (ASInterface && AbilitySet)
	{
		AbilitySet->GiveAbilities(ASInterface->GetAbilitySystemComponent());
	}
	
}

const UAbilitySet* UAbilitySetComponent::GetAbilitySet() const
{
	return AbilitySet;
}


