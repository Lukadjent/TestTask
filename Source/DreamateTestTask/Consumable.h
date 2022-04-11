// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Item.h"
#include "Consumable.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API AConsumable : public AItem
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Montages")
	UAnimMontage* UsageMontage;

	TSubclassOf<UGameplayEffect> Effect;
	
};
