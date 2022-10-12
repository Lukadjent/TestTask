// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/RotatingSpringArmComponent.h"
#include "InputActionValue.h"


void URotatingSpringArmComponent::RotateCamera(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Yellow, FString::Printf(TEXT("RotatingSpringArmComponent : RotatingCamera")));
	FRotator Rotation = GetComponentRotation();
	Rotation.Yaw -= Value[0] * CameraAngleSpeed;
	Rotation.Pitch = FMath::Clamp(Rotation.Pitch - Value[1] * CameraAngleSpeed, -70.f, 70.f);
	SetWorldRotation(Rotation);
}

