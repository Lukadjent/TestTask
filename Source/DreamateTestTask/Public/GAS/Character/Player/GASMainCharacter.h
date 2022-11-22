// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraInterface.h"
#include "Components/InteractionComponent.h"
#include "GAS/Character/AI/GASBaseCharacter.h"
#include "GAS/Ability/AbilityBindingInterface.h"
#include "Input/AbilityBindingInputComponent.h"
#include "Interfaces/InteractionComponentInterface.h"
#include "GASMainCharacter.generated.h"

class UAbilitySet;
/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API AGASMainCharacter : public AGASBaseCharacter, public ICameraInterface,
                                               public IAbilityBindingInterface, public IInteractionComponentInterface
{
	GENERATED_BODY()

	AGASMainCharacter();

	virtual void BeginPlay() override;
	
	virtual void PawnClientRestart() override;

protected:
#pragma region COMPONENTS

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<URotatingSpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UMovingCameraComponent> CameraComponent;

	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAbilitySetComponent> AbilitySetComponent;
	
	float SpringArmLength = 1000.f;

	TObjectPtr<UAbilityBindingInputComponent> AbilityBindingInputComponent;

	TObjectPtr<UInteractionComponent> InteractionComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UGASCharacterComponent> GASCharacterComponent;

#pragma endregion
	
public:
	
	void LoseControlTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	virtual UMovingCameraComponent* GetMovingCameraComponent() const override;

	virtual URotatingSpringArmComponent* GetRotatingSpringArmComponent() const override;

	virtual void BindAbility(FGameplayAbilitySpec& Spec) const override;

	virtual void UnbindAbility(FGameplayAbilitySpec& Spec) const override;

	virtual UInteractionComponent* GetInteractionComponent() const override;
};
