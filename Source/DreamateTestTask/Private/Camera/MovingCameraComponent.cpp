#include "Camera/MovingCameraComponent.h"
#include "InputActionValue.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UMovingCameraComponent::UMovingCameraComponent()
{
	
}

void UMovingCameraComponent::MoveCamera(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Yellow, FString::Printf(TEXT("MovingCameraComponent : MovingCamera")));
	const float Angle = GetRelativeRotation().Yaw;
	const FVector Direction (UKismetMathLibrary::GetRotated2D(FVector2d(Value[0], Value[1]), Angle), 0.f);
	//Calculate And Set New Location For Camera
	FVector Location = GetRelativeLocation();
	Location += CameraMoveSpeed * Direction;
	SetRelativeLocation(Location, true);
}

void UMovingCameraComponent::AttachCameraToComponent(USceneComponent* Component, FName SocketName)
{
	if (bIsCameraAttached)
	{
		AttachToComponent(Component, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), SocketName);
		bIsCameraAttached = true;
	}
}

void UMovingCameraComponent::DetachCameraFromParent()
{
	if (bIsCameraAttached)
	{
		DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
		bIsCameraAttached = false;
	}
}

