// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/ASComponent.h"
#include "Input/AbilityBindingInputComponent.h"
#include "AbilitySet.generated.h"

USTRUCT()
struct FGameplayAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = BindInfo)
	TSoftClassPtr<class UGameplayAbility> GameplayAbilityClass;

	UPROPERTY(EditAnywhere, Category = BindInfo)
	TSoftObjectPtr<class UInputAction> InputAction;

	UPROPERTY(EditAnywhere, Category = BindInfo)
	bool bShouldBeGivenOnSpawn;
};

UCLASS(BlueprintType, Const)
class DREAMATETESTTASK_API UAbilitySet : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = AbilitySet)
	TArray<FGameplayAbilityInfo> Abilities;
	UPROPERTY(EditAnywhere, Category = AbilitySet)
	TArray<TSoftClassPtr<UGameplayAbility>> PassiveAbilities;

public:

	void GiveAbilities(UASComponent* AbilitySystemComponent) const;

	void BindAbility(UAbilityBindingInputComponent* InputComponent, struct FGameplayAbilitySpec& Spec) const;

	void UnbindAbility(UAbilityBindingInputComponent* InputComponent, struct FGameplayAbilitySpec& Spec) const;
	
};
