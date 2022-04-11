// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_SendEvent.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API UAN_SendEvent : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Event")
	FGameplayTag NotifyTag;
};
