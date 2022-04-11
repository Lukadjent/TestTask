// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagsSettings.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_SendEvent.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API UANS_Attack : public UAnimNotifyState
{
	GENERATED_BODY()
	
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	FGameplayTag EventBegin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	FGameplayTag EventEnd;

	UPROPERTY()
	AActor* Actor;
};
