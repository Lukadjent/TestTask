// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_BaseActionCost.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API UMMC_BaseActionCost : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

	UMMC_BaseActionCost();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition Stamina;

	const float BaseActionStaminaCost = 20.f;
};
