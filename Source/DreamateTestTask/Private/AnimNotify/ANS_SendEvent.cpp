// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamateTestTask/Public/AnimNotify/ANS_SendEvent.h"

#include "AbilitySystemBlueprintLibrary.h"

void UANS_Attack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Actor = MeshComp->GetOwner();
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Actor, EventBegin, FGameplayEventData());
}

void UANS_Attack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Actor, EventEnd, FGameplayEventData());
}
