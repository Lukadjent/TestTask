// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilityBase.h"

#include "GAS/Character/AI/GASBaseCharacter.h"

FGameplayEffectContainerSpec UAbilityBase::MakeEffectContainerSpecFromContainer(
	const FGameplayEffectContainer& Container, const FGameplayEventData& EventData)
{
	FGameplayEffectContainerSpec ReturnSpec;
	AActor* OwningActor = GetOwningActorFromActorInfo();
	AGASBaseCharacter* OwningCharacter = Cast<AGASBaseCharacter>(OwningActor);
	if (GetAbilitySystemComponentFromActorInfo())
	{
		if (Container.TargetType.Get())
		{
			TArray<FHitResult> HitResults;
			TArray<AActor*> TargetActors;
			const UTargetType* TargetTypeCDO = Container.TargetType.GetDefaultObject();
			AActor* AvatarActor = GetAvatarActorFromActorInfo();
			TargetTypeCDO->GetTargets_Implementation(OwningCharacter, AvatarActor, EventData, HitResults, TargetActors);
			ReturnSpec.AddTargets(HitResults, TargetActors);
		}
		for (const TSubclassOf<UGameplayEffect>& EffectClass : Container.TargetGameplayEffectClasses)
		{
			ReturnSpec.TargetGameplayEffectSpecs.Add(MakeOutgoingGameplayEffectSpec(EffectClass));
		}
	}
	return ReturnSpec;
}

FGameplayEffectContainerSpec UAbilityBase::MakeEffectContainerSpec(FGameplayTag ContainerTag,
                                                                   const FGameplayEventData& EventData)
{
	FGameplayEffectContainer* FoundContainer = EffectContainerMap.Find(ContainerTag);
	if (FoundContainer)
	{
		return MakeEffectContainerSpecFromContainer(*FoundContainer, EventData);
	}
	return FGameplayEffectContainerSpec();
}

TArray<FActiveGameplayEffectHandle> UAbilityBase::ApplyEffectContainerSpec(
	const FGameplayEffectContainerSpec& ContainerSpec)
{
	TArray<FActiveGameplayEffectHandle> AllEffects;

	for (const FGameplayEffectSpecHandle& SpecHandle : ContainerSpec.TargetGameplayEffectSpecs)
	{
		AllEffects.Append(K2_ApplyGameplayEffectSpecToTarget(SpecHandle, ContainerSpec.TargetData));
	}
	return AllEffects;
}

TArray<FActiveGameplayEffectHandle> UAbilityBase::ApplyEffectContainer(FGameplayTag ContainerTag,
                                                                       const FGameplayEventData& EventData)
{
	FGameplayEffectContainerSpec Spec = MakeEffectContainerSpec(ContainerTag, EventData);
	return ApplyEffectContainerSpec(Spec);
}
