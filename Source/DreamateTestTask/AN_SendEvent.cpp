// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_SendEvent.h"

#include "AbilitySystemBlueprintLibrary.h"

void UAN_SendEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), NotifyTag, FGameplayEventData());
}
