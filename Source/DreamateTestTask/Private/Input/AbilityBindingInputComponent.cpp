// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AbilityBindingInputComponent.h"

#include "AbilitySystemComponent.h"
#include "GAS/AbilitySystemComponentInterface.h"
#include "AbilitySystemGlobals.h"
#include "GAS/Ability/AbilitySet.h"

namespace AbilityInputBindingComponent_Impl
{
	constexpr int32 InvalidInputID = 0;
	int32 IncrementingInputID = InvalidInputID;

	static int32 GetNextInputID()
	{
		return ++IncrementingInputID;
	}
}

void UAbilityBindingInputComponent::SetInputBinding(UInputAction* InputAction, FGameplayAbilitySpec& AbilitySpec)
{

	using namespace AbilityInputBindingComponent_Impl;
	
	if (AbilitySpec.InputID == InvalidInputID)
	{
		AbilitySpec.InputID = GetNextInputID();
	}

	FAbilityInputBinding* AbilityInputBinding = MappedAbilities.Find(InputAction);

	if (!AbilityInputBinding)
	{
		AbilityInputBinding = &MappedAbilities.Add(InputAction);
	}
	
	AbilityInputBinding->BoundAbilitiesStack.AddUnique(AbilitySpec.Handle);

	AbilityInputBinding->InputID = AbilitySpec.InputID;
	
	if (InputComponent)
	{
		if (AbilityInputBinding->OnPressedHandle == 0)
		{
			AbilityInputBinding->OnPressedHandle = InputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &UAbilityBindingInputComponent::OnAbilityInputPressed, InputAction).GetHandle();
		}
		
		if (AbilityInputBinding->OnReleasedHandle == 0)
		{
			AbilityInputBinding->OnReleasedHandle = InputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &UAbilityBindingInputComponent::OnAbilityInputReleased, InputAction).GetHandle();
		}
	}
}

void UAbilityBindingInputComponent::ClearInputBinding(FGameplayAbilitySpec& AbilitySpec)
{
	using namespace AbilityInputBindingComponent_Impl;
	
	TArray<UInputAction*> InputActionsToClear;
	for (auto& InputBinding : MappedAbilities)
	{
		if (InputBinding.Value.BoundAbilitiesStack.Contains(AbilitySpec.Handle))
		{
			InputActionsToClear.Add(InputBinding.Key);
		}
	}

	for (UInputAction* InputAction : InputActionsToClear)
	{
		FAbilityInputBinding* AbilityInputBinding = MappedAbilities.Find(InputAction);
		if (AbilityInputBinding->BoundAbilitiesStack.Remove(AbilitySpec.Handle) > 0)
		{
			if (AbilityInputBinding->BoundAbilitiesStack.Num() == 0)
			{
				RemoveEntry(InputAction);
			}
		}
	}
	
	AbilitySpec.InputID = InvalidInputID;
}

void UAbilityBindingInputComponent::OnRegister()
{
	Super::OnRegister();
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (ensure(Pawn) && Pawn->InputComponent)
	{
		InputComponent = CastChecked<UEnhancedInputComponent>(Pawn->InputComponent);
	}
}

void UAbilityBindingInputComponent::RunAbilitySystemSetup()
{
	check(GetOwner());

	AbilityComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());;

	if (AbilityComponent)
	{
		for (TTuple<UInputAction*, FAbilityInputBinding>& InputBinding : MappedAbilities)
		{
			const int32 NewInputID = AbilityInputBindingComponent_Impl::GetNextInputID();
			InputBinding.Value.InputID = NewInputID;
			for (const FGameplayAbilitySpecHandle AbilityHandle : InputBinding.Value.BoundAbilitiesStack)
			{
				FGameplayAbilitySpec* FoundAbility = AbilityComponent->FindAbilitySpecFromHandle(AbilityHandle);
				if (FoundAbility)
				{
					FoundAbility->InputID = NewInputID;
				}
			}
		}
	}
}

void UAbilityBindingInputComponent::OnAbilityInputPressed(UInputAction* InputAction)
{
	if (!AbilityComponent)
	{
		RunAbilitySystemSetup();
	}
	if (AbilityComponent)
	{
		using namespace  AbilityInputBindingComponent_Impl;

		const FAbilityInputBinding* FoundBinding = MappedAbilities.Find(InputAction);
		if (FoundBinding)
		{
			for (const FGameplayAbilitySpecHandle AbilityHandle : FoundBinding->BoundAbilitiesStack)
			{
				const FGameplayAbilitySpec* FoundAbility = AbilityComponent->FindAbilitySpecFromHandle(AbilityHandle);
				if (FoundAbility != nullptr && ensure(FoundAbility->InputID != InvalidInputID))
				{
					AbilityComponent->AbilityLocalInputPressed(FoundAbility->InputID);
				}
			}
		}
	}
}

void UAbilityBindingInputComponent::OnAbilityInputReleased(UInputAction* InputAction)
{
	if (AbilityComponent)
	{
		using namespace  AbilityInputBindingComponent_Impl;

		const FAbilityInputBinding* FoundBinding = MappedAbilities.Find(InputAction);
		if (FoundBinding && ensure(FoundBinding->InputID != InvalidInputID))
		{
			AbilityComponent->AbilityLocalInputReleased(FoundBinding->InputID);
		}
	}
}

void UAbilityBindingInputComponent::RemoveEntry(const UInputAction* InputAction)
{
	if (FAbilityInputBinding* Bindings = MappedAbilities.Find(InputAction))
	{
		if (InputComponent)
		{
			InputComponent->RemoveBindingByHandle(Bindings->OnPressedHandle);
			InputComponent->RemoveBindingByHandle(Bindings->OnReleasedHandle);
		}
		
		for (const FGameplayAbilitySpecHandle &AbilityHandle : Bindings->BoundAbilitiesStack)
		{
			using namespace AbilityInputBindingComponent_Impl;

			FGameplayAbilitySpec* AbilitySpec = FindAbilitySpec(AbilityHandle);
			if (AbilitySpec && AbilitySpec->InputID == Bindings->InputID)
			{
				AbilitySpec->InputID = InvalidInputID;	
			}
		}
		
		MappedAbilities.Remove(InputAction);
		
	}
}

FGameplayAbilitySpec* UAbilityBindingInputComponent::FindAbilitySpec(FGameplayAbilitySpecHandle Handle) const
{
	FGameplayAbilitySpec* FoundAbility = nullptr;
	if (AbilityComponent)
	{
		FoundAbility = AbilityComponent->FindAbilitySpecFromHandle(Handle);
	}
	return FoundAbility;
}
