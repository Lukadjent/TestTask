// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GC_PlaySound.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API UGC_PlaySound : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Sound")
	USoundBase* Sound;

	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;
};
