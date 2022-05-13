// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Enum/EAbilities.h"
#include "GameFramework/Character.h"
#include "GAS/AttributeSet/BaseAttributeSet.h"
#include "Inventory/InventoryTypes.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "GASBaseCharacter.generated.h"

class UInventoryComponent;

UCLASS()
class DREAMATETESTTASK_API AGASBaseCharacter : public ACharacter, public IAbilitySystemInterface
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
	UAbilitySystemComponent* AbilitySystemComponent;

#pragma endregion
	
	UPROPERTY(EditDefaultsOnly)
	UBaseAttributeSet* AttributeSet;

	//Initialize attributes, Stamina regeneration
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	void InitializeDefaultAttributesAndEffects();

	//Abilities character gets from weapon slots
	TMap<FItemSlot, FGameplayAbilitySpecHandle> SlottedAbilities;

	//Abilities character has by default
	UPROPERTY(EditDefaultsOnly)
	TMap<EAbilities, TSubclassOf<UGameplayAbility>> StandardAbilities;

	void OnMovementSpeedChange(const FOnAttributeChangeData& Data);

	//On add or remove immobile tag
	virtual void ImmobileTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

public:	

	//Activate ability given by item that is slotted
	UFUNCTION()
	bool ActivateAbilitiesWithItemSlot(FItemSlot ItemSlot);

	//Remove ability when slotted item changes
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void RemoveSlottedGameplayAbilities(FItemSlot InSlot);

	//Add ability when slotted item changes
	UFUNCTION()
	void AddSlottedGameplayAbilities();
	
	UFUNCTION()
	void FillSlottedAbilitySpecs(TMap<FItemSlot, FGameplayAbilitySpec>& SlottedAbilitySpecs);

	//Delegate on Character Death
	DECLARE_MULTICAST_DELEGATE_OneParam(FCharacterDeath, AGASBaseCharacter*);
	FCharacterDeath CharacterDeath;
	
	UFUNCTION(BlueprintCallable)
	void NotifyDeath();

	//Attack Function
	bool Attack();

#pragma region COMPONENT_GETTERS
	
	UInventoryComponent* GetInventoryComponent() const;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UChildActorComponent* GetWeaponComponent() const;

#pragma endregion

};