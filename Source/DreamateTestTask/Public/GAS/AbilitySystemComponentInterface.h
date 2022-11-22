// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet/BaseAttributeSet.h"
#include "UObject/Interface.h"
#include "AbilitySystemComponentInterface.generated.h"

class UASComponent;

// This class does not need to be modified.
UINTERFACE()
class UAbilitySystemComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DREAMATETESTTASK_API IAbilitySystemComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual UASComponent* GetAbilitySystemComponent() const = 0;

	virtual UBaseAttributeSet* GetAttributeSet() const = 0;
};
