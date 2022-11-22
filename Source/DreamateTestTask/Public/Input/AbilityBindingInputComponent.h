// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayAbilitySpec.h"
#include "GameFramework/PawnMovementComponent.h"
#include "UObject/Object.h"
#include "AbilityBindingInputComponent.generated.h"

USTRUCT()
struct FAbilityInputBinding
{
	GENERATED_BODY()

	int32 InputID = 0;
	uint32 OnPressedHandle = 0;
	uint32 OnReleasedHandle = 0;
	TArray<FGameplayAbilitySpecHandle> BoundAbilitiesStack;
};


UCLASS()
class DREAMATETESTTASK_API UAbilityBindingInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	void SetInputBinding(UInputAction* InputAction, FGameplayAbilitySpec& AbilitySpec);

	void ClearInputBinding(FGameplayAbilitySpec& AbilitySpec);
	
private:

	virtual void OnRegister() override;

	void RunAbilitySystemSetup();

	void OnAbilityInputPressed(UInputAction* InputAction);
	
	void OnAbilityInputReleased(UInputAction* InputAction);
	
	void RemoveEntry(const UInputAction* InputAction);
	
	
	UPROPERTY(Transient)
	UAbilitySystemComponent* AbilityComponent;

	UPROPERTY(Transient)
	UEnhancedInputComponent* InputComponent;

public:
	UPROPERTY(Transient)
	TMap<UInputAction*, FAbilityInputBinding> MappedAbilities;

	FGameplayAbilitySpec* FindAbilitySpec(FGameplayAbilitySpecHandle Handle) const;
};

