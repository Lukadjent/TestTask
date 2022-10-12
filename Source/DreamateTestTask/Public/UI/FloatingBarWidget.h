// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributesWidgetInterface.h"
#include "Blueprint/UserWidget.h"
#include "FloatingBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API UFloatingBarWidget : public UUserWidget, public IAttributesWidgetInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateColor(FLinearColor Color);
};
