// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InteractionComponent.h"
#include "UObject/Interface.h"
#include "InteractionComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteractionComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DREAMATETESTTASK_API IInteractionComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual UInteractionComponent* GetInteractionComponent() const = 0;
};
