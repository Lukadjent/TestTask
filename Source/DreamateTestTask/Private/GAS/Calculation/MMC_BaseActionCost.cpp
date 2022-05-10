// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Calculation/MMC_BaseActionCost.h"
#include "GAS/AttributeSet/BaseAttributeSet.h"
#include "GAS/Character/Player/GASMainCharacter.h"

UMMC_BaseActionCost::UMMC_BaseActionCost()
{
	Stamina.AttributeToCapture = UBaseAttributeSet::GetStaminaAttribute();
	Stamina.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	Stamina.bSnapshot = false;

	RelevantAttributesToCapture.Add(Stamina);
}

float UMMC_BaseActionCost::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	if (Spec.GetContext().GetInstigator()->IsA(AGASMainCharacter::StaticClass()))
	{
		float StaminaValue = 0.f;
		GetCapturedAttributeMagnitude(Stamina, Spec, EvaluationParameters, StaminaValue);
	
	
		if (StaminaValue < BaseActionStaminaCost && StaminaValue > 10.f)
		{
			return StaminaValue;
		}

		return BaseActionStaminaCost;
	}
	
	return 0.f;
}
