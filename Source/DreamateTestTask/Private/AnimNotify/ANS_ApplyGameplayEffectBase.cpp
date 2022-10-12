// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/ANS_ApplyGameplayEffectBase.h"

void UANS_ApplyGameplayEffectBase::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	IAbilitySystemComponentInterface* ASCInterface = Cast<IAbilitySystemComponentInterface>(MeshComp->GetOwner());
	if (ASCInterface)
	{
		AbilitySystemComponent = ASCInterface->GetAbilitySystemComponent();
		if (AbilitySystemComponent)
		{
			const FGameplayEffectContextHandle GameplayEffectContext = AbilitySystemComponent->MakeEffectContext();
			const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, GameplayEffectContext);
			AbilitySystemComponent->BP_ApplyGameplayEffectSpecToSelf(SpecHandle);
		}
	}
}

void UANS_ApplyGameplayEffectBase::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (AbilitySystemComponent)
	{
	AbilitySystemComponent->RemoveActiveGameplayEffectBySourceEffect(GameplayEffect, nullptr);
	}
}
