// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "TargetType.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "AbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FGameplayEffectContainer
{
	GENERATED_BODY()

public:
	FGameplayEffectContainer() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectContainer")
	TSubclassOf<UTargetType> TargetType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectContainer")
	TArray<TSubclassOf<UGameplayEffect>> TargetGameplayEffectClasses;
};

USTRUCT(BlueprintType)
struct FGameplayEffectContainerSpec
{
	GENERATED_BODY()

public:

	FGameplayEffectContainerSpec() {}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectContainer")
	FGameplayAbilityTargetDataHandle TargetData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectContainer")
	TArray<FGameplayEffectSpecHandle> TargetGameplayEffectSpecs;

	bool HasValidEffect() const;

	bool HasValidTargets() const;

	void AddTargets(const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors);
};
