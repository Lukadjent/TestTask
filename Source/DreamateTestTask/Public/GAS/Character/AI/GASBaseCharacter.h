// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Enum/EAbilities.h"
#include "GameFramework/Character.h"
#include "GAS/AbilitySystemComponentInterface.h"
#include "GAS/ASComponent.h"
#include "GAS/AttributeSet/BaseAttributeSet.h"
#include "Inventory/InventoryInterface.h"
#include "Inventory/InventoryTypes.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "GASBaseCharacter.generated.h"

class UInventoryComponent;

UCLASS()
class DREAMATETESTTASK_API AGASBaseCharacter : public ACharacter, public IAbilitySystemComponentInterface, public IInventoryInterface
{
	GENERATED_BODY()

protected:
	AGASBaseCharacter();
	
	virtual void BeginPlay() override;

#pragma region COMPONENTS
	
	UPROPERTY(EditDefaultsOnly, Category = "Perception")
	UAIPerceptionStimuliSourceComponent* StimuliSourceComponent;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UChildActorComponent* WeaponComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Inventory")
	UInventoryComponent* Inventory;
	
	UPROPERTY(EditDefaultsOnly)
	UASComponent* AbilitySystemComponent;

#pragma endregion
	
	UPROPERTY(EditDefaultsOnly)
	UBaseAttributeSet* AttributeSet;

	//Initialize attributes, Stamina regeneration
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	void InitializeDefaultAttributesAndEffects();
	
	void OnMovementSpeedChange(const FOnAttributeChangeData& Data);

	//On add or remove immobile tag
	virtual void ImmobileTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	void SlottedItemChanged(FItemSlot ItemSlot, UItemData* Item);

public:
	
	//Delegate on Character Death
	DECLARE_MULTICAST_DELEGATE_OneParam(FCharacterDeath, AGASBaseCharacter*);
	FCharacterDeath CharacterDeath;
	
	UFUNCTION(BlueprintCallable)
	void NotifyDeath();


#pragma region COMPONENT_GETTERS

	virtual UASComponent* GetAbilitySystemComponent() const override;
	
	virtual UInventoryComponent* GetInventoryComponent() const override;

	UChildActorComponent* GetWeaponComponent() const;

#pragma endregion
	
};
