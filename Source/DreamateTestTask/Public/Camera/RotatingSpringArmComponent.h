// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "RotatingSpringArmComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DREAMATETESTTASK_API URotatingSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Camera", meta = (AllowPrivateAccess))
	float CameraAngleSpeed = 1.f; 
	
public:

	void RotateCamera(const FInputActionValue& Value);
};
