// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/Interface.h"
#include "MovementComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMovementComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DREAMATETESTTASK_API IMovementComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual UCharacterMovementComponent* GetCharacterMovementComponent() const = 0;
};
