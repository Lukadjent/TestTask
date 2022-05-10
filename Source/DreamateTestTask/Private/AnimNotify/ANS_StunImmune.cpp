// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/ANS_StunImmune.h"

void UANS_StunImmune::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Character = Cast<AGASBaseCharacter>(MeshComp->GetOwner());
	if (Character)
	{
		const FGameplayEffectContextHandle GameplayEffectContext = Character->GetAbilitySystemComponent()->MakeEffectContext();
		const FGameplayEffectSpecHandle SpecHandle = Character->GetAbilitySystemComponent()->MakeOutgoingSpec(GE_StunImmune, 1, GameplayEffectContext);
		Character->GetAbilitySystemComponent()->BP_ApplyGameplayEffectSpecToSelf(SpecHandle);
	}
}

void UANS_StunImmune::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (Character)
	{
		Character->GetAbilitySystemComponent()->RemoveActiveGameplayEffectBySourceEffect(GE_StunImmune, nullptr);
	}
}
