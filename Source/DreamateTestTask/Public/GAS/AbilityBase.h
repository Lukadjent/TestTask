// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityTypes.h"
#include "Abilities/GameplayAbility.h"
#include "AbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API UAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UAbilityBase() {}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayEffects")
	TMap<FGameplayTag, FGameplayEffectContainer> EffectContainerMap;

	UFUNCTION(BlueprintCallable, Category = "Ability", meta = (AutoCreateRefTerm = "EventData"))
	virtual FGameplayEffectContainerSpec MakeEffectContainerSpecFromContainer(const FGameplayEffectContainer& Container, const FGameplayEventData& EventData);

	UFUNCTION(BlueprintCallable, Category = "Ability", meta = (AutoCreateRefTerm = "EventData"))
	virtual FGameplayEffectContainerSpec MakeEffectContainerSpec(FGameplayTag ContainerTag, const FGameplayEventData& EventData);
	
	UFUNCTION(BlueprintCallable, Category = "Ability", meta = (AutoCreateRefTerm = "EventData"))
	virtual TArray<FActiveGameplayEffectHandle> ApplyEffectContainerSpec(const FGameplayEffectContainerSpec& ContainerSpec);

	UFUNCTION(BlueprintCallable, Category = "Ability", meta = (AutoCreateRefTerm = "EventData"))
	virtual TArray<FActiveGameplayEffectHandle> ApplyEffectContainer(FGameplayTag ContainerTag, const FGameplayEventData& EventData);
	
};
