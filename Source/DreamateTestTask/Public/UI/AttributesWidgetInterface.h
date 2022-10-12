// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "UObject/Interface.h"
#include "AttributesWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UAttributesWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DREAMATETESTTASK_API IAttributesWidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetAttribute(FGameplayAttribute Attribute);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetAttributeMax(FGameplayAttribute Attribute);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetAbilitySystemComponent(const UAbilitySystemComponent* ASC);
};
