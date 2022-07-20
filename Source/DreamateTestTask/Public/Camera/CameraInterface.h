// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RotatingSpringArmComponent.h"
#include "UObject/Interface.h"
#include "CameraInterface.generated.h"

class UMovingCameraComponent;
class URotatingSpringArmComponent;

// This class does not need to be modified.
UINTERFACE()
class UCameraInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DREAMATETESTTASK_API ICameraInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual UMovingCameraComponent* GetMovingCameraComponent() const = 0;

	virtual URotatingSpringArmComponent* GetRotatingSpringArmComponent() const = 0;
};
