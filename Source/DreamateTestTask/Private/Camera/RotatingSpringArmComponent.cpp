// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/RotatingSpringArmComponent.h"
#include "InputActionValue.h"


// Sets default values for this component's properties
URotatingSpringArmComponent::URotatingSpringArmComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URotatingSpringArmComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URotatingSpringArmComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URotatingSpringArmComponent::RotateCamera(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Yellow, FString::Printf(TEXT("RotatingSpringArmComponent : RotatingCamera")));
	FRotator Rotation = GetRelativeRotation();
	Rotation.Yaw -= Value[0] * CameraAngleSpeed;
	SetRelativeRotation(Rotation);
}

