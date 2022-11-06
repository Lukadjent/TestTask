// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PatrolComponent.h"
#include "UObject/Interface.h"
#include "PatrolInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPatrolInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DREAMATETESTTASK_API IPatrolInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual UPatrolComponent* GetPatrolComponent() const = 0;
};
