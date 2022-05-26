// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/ANS_ApplyGameplayEffectBase.h"

void UANS_ApplyGameplayEffectBase::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Character = Cast<AGASBaseCharacter>(MeshComp->GetOwner());
	if (Character)
	{
		const FGameplayEffectContextHandle GameplayEffectContext = Character->GetAbilitySystemComponent()->MakeEffectContext();
		const FGameplayEffectSpecHandle SpecHandle = Character->GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffect, 1, GameplayEffectContext);
		Character->GetAbilitySystemComponent()->BP_ApplyGameplayEffectSpecToSelf(SpecHandle);
	}
}

void UANS_ApplyGameplayEffectBase::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (Character)
	{
		Character->GetAbilitySystemComponent()->RemoveActiveGameplayEffectBySourceEffect(GameplayEffect, nullptr);
	}
}
