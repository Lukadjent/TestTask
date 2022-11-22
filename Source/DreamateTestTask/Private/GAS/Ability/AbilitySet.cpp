// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/AbilitySet.h"

void UAbilitySet::GiveAbilities(UASComponent* AbilitySystemComponent) const
{
	for (TSoftClassPtr<UGameplayAbility> Ability : PassiveAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability.LoadSynchronous(), 0, -10));
	}
	
	for (const FGameplayAbilityInfo& AbilityInfo : Abilities)
	{
		if (AbilityInfo.bShouldBeGivenOnSpawn)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityInfo.GameplayAbilityClass.LoadSynchronous(), 0, 0));
		}
	}
}

void UAbilitySet::BindAbility(UAbilityBindingInputComponent* InputComponent, FGameplayAbilitySpec& Spec) const
{
	check(Spec.Ability);
	check(InputComponent);

	for (const FGameplayAbilityInfo& BindInfo : Abilities)
	{
		if (BindInfo.GameplayAbilityClass.LoadSynchronous() == Spec.Ability->GetClass() || Spec.Ability->GetClass()->IsChildOf(BindInfo.GameplayAbilityClass.LoadSynchronous()))
		{
			InputComponent->SetInputBinding(BindInfo.InputAction.LoadSynchronous(), Spec);
		}
	}
}

void UAbilitySet::UnbindAbility(UAbilityBindingInputComponent* InputComponent, FGameplayAbilitySpec& Spec) const
{
	check(InputComponent);
	InputComponent->ClearInputBinding(Spec);
}
