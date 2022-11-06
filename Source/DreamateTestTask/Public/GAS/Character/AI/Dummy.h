// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GAS/Character/AI/GASBaseCharacter.h"
#include "UI/FloatingBarWidget.h"
#include "Dummy.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API ADummy : public AGASBaseCharacter
{
	GENERATED_BODY()

protected:
	
	ADummy();

	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<UFloatingBarWidget> FloatingBarWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI|Bar")
	TSubclassOf<UFloatingBarWidget> FloatingBarClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TObjectPtr<UWidgetComponent> WidgetComponent;

	virtual void ImmobileTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;
};
