// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraInterface.h"
#include "GAS/Character/AI/GASBaseCharacter.h"
#include "GASMainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API AGASMainCharacter : public AGASBaseCharacter, public ICameraInterface
{
	GENERATED_BODY()

	AGASMainCharacter();

	virtual void BeginPlay() override;
	
	virtual void PawnClientRestart() override;

	virtual void ImmobileTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;

public: 
#pragma region CAMERA

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	URotatingSpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UMovingCameraComponent* CameraComponent;
	
	float SpringArmLength = 1000.f;
	
#pragma endregion

#pragma region ABILITIES
	
	void Roll();

	void Parry();

	void CastSpell();

	bool UseConsumable();

#pragma endregion
	
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle MaxManaChangedDelegateHandle;
	FDelegateHandle MaxStaminaChangedDelegateHandle;
	FDelegateHandle StaminaRegenRateChangedDelegateHandle;
	
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxManaChanged(const FOnAttributeChangeData& Data);
	virtual void MaxStaminaChanged(const FOnAttributeChangeData& Data);
	virtual void StaminaRegenRateChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintCallable, Category = "GASDocumentation|GDPlayerState|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GASDocumentation|GDPlayerState|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GASDocumentation|GDPlayerState|Attributes")
	float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "GASDocumentation|GDPlayerState|Attributes")
	float GetMaxMana() const;

	UFUNCTION(BlueprintCallable, Category = "GASDocumentation|GDPlayerState|Attributes")
	float GetStamina() const;

	UFUNCTION(BlueprintCallable, Category = "GASDocumentation|GDPlayerState|Attributes")
	float GetMaxStamina() const;

	virtual UMovingCameraComponent* GetMovingCameraComponent() const override;

	virtual URotatingSpringArmComponent* GetRotatingSpringArmComponent() const override;
};
