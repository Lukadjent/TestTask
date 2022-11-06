// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Enum/EAbilities.h"
#include "GameFramework/Character.h"
#include "GAS/AbilitySystemComponentInterface.h"
#include "GAS/ASComponent.h"
#include "GAS/AttributeSet/BaseAttributeSet.h"
#include "Interfaces/Death.h"
#include "Inventory/InventoryInterface.h"
#include "Inventory/InventoryTypes.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "GASBaseCharacter.generated.h"

class UInventoryComponent;

UCLASS()
class DREAMATETESTTASK_API AGASBaseCharacter : public ACharacter, public IAbilitySystemComponentInterface, public IInventoryInterface, public IDeath
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

#pragma endregion
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBaseAttributeSet> AttributeSet;

	//Initialize attributes, Stamina regeneration
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	void InitializeDefaultAttributesAndEffects();
	
	void OnMovementSpeedChange(const FOnAttributeChangeData& Data);

	//On add or remove immobile tag
	virtual void ImmobileTagChanged(const FGameplayTag CallbackTag, int32 NewCount) PURE_VIRTUAL(AGASBaseCharacter::ImmobileTagChanged, );

	void SlottedItemChanged(FItemSlot ItemSlot, UItemData* Item);

public:
	virtual void NotifyDeath_Implementation() const override;


#pragma region COMPONENT_GETTERS

	virtual UASComponent* GetAbilitySystemComponent() const override;
	
	virtual UInventoryComponent* GetInventoryComponent() const override;

	UChildActorComponent* GetWeaponComponent() const;

#pragma endregion
	
};
