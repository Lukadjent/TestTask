// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FloatingBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API UFloatingBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentHealth(float CurrentHealth);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxHealth(float MaxHealth);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetHealthPercantage(float HealthPercentage);
};
