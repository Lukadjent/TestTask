// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GAS/Character/AI/GASBaseCharacter.h"
#include "ANS_ApplyGameplayEffectBase.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API UANS_ApplyGameplayEffectBase : public UAnimNotifyState
{
	GENERATED_BODY()

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY()
	AGASBaseCharacter* Character;
	
protected:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GameplayEffect")
	TSubclassOf<UGameplayEffect> GameplayEffect;
	
};
