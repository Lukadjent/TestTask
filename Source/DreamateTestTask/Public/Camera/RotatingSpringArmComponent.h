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

public:
	// Sets default values for this component's properties
	URotatingSpringArmComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Camera")
	float CameraAngleSpeed = 1.f; 
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void RotateCamera(const FInputActionValue& Value);
};
