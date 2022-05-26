// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Calculation/GEEC_CalculateDamage.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GAS/AttributeSet/BaseAttributeSet.h"

struct GDDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(IncomingDamage);

	GDDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, IncomingDamage, Source, true);
	}
};

static const GDDamageStatics& DamageStatics()
{
	static GDDamageStatics DStatics;
	return DStatics;
}


UGEEC_CalculateDamage::UGEEC_CalculateDamage()
{
	RelevantAttributesToCapture.Add(DamageStatics().IncomingDamageDef);
}

void UGEEC_CalculateDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                   FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Damage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().IncomingDamageDef, EvaluationParameters, Damage);
	if (TargetTags->HasTag(FGameplayTag::RequestGameplayTag(StunTag)))
	{
		Damage *= 1.5f;
	}
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().IncomingDamageProperty, EGameplayModOp::Override, Damage));
	
}
