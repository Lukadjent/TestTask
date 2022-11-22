// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CharacterWidgetComponent.h"
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

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TObjectPtr<UCharacterWidgetComponent> WidgetComponent;
	
};
