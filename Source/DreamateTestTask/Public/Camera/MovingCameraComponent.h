// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraInterface.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "MovingCameraComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DREAMATETESTTASK_API UMovingCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovingCameraComponent();

private:
	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Camera|Settings")
	const float CameraMoveSpeed = 20.f;

	bool bIsCameraAttached = true;


public:	
	void MoveCamera(const FInputActionValue& Value);

	void AttachCameraToComponent(USceneComponent* Component, FName SocketName = NAME_None);

	void DetachCameraFromParent();
};
