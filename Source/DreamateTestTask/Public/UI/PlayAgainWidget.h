// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayAgainWidget.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API UPlayAgainWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetText(const FString& Text);
};
