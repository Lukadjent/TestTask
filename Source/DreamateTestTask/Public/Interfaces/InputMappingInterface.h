// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputMappingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInputMappingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DREAMATETESTTASK_API IInputMappingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual TMap<class UInputMappingContext*, int32> GetInputContextsMap() const = 0;
};
