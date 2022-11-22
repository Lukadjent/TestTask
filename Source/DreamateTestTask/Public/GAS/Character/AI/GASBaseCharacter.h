// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Components/AbilitySetComponent.h"
#include "Components/GASCharacterComponent.h"
#include "GameFramework/Character.h"
#include "GAS/AbilitySystemComponentInterface.h"
#include "GAS/ASComponent.h"
#include "GAS/AttributeSet/BaseAttributeSet.h"
#include "Interfaces/Death.h"
#include "Interfaces/MovementComponentInterface.h"
#include "Inventory/InventoryInterface.h"
#include "Inventory/InventoryTypes.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "GASBaseCharacter.generated.h"

class UAbilitySet;
class UInventoryComponent;

UCLASS()
class DREAMATETESTTASK_API AGASBaseCharacter : public ACharacter, public IAbilitySystemComponentInterface, public IInventoryInterface, public IDeath, public IMovementComponentInterface
{
	GENERATED_BODY()

protected:
	
	AGASBaseCharacter();
	
	virtual void BeginPlay() override;

#pragma region COMPONENTS
	
	UPROPERTY(EditDefaultsOnly, Category = "Perception")
	TObjectPtr<UAIPerceptionStimuliSourceComponent> StimuliSourceComponent;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UChildActorComponent> WeaponComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Inventory")
	TObjectPtr<UInventoryComponent> Inventory;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UASComponent> AbilitySystemComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBaseAttributeSet> AttributeSet;

#pragma endregion 

public:

	virtual void NotifyDeath_Implementation() const override;

#pragma region COMPONENT_GETTERS

	virtual UASComponent* GetAbilitySystemComponent() const override;
	
	virtual UInventoryComponent* GetInventoryComponent() const override;

	virtual UChildActorComponent* GetWeaponComponent() const override;

	virtual UBaseAttributeSet* GetAttributeSet() const override;

	virtual UCharacterMovementComponent* GetCharacterMovementComponent() const override;

#pragma endregion
	
};
