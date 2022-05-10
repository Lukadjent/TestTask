// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Enum/EAbilities.h"
#include "Enum/EWeaponType.h"
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
	
	// Sets default values for this character's properties
	AGASBaseCharacter();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Perception")
	UAIPerceptionStimuliSourceComponent* StimuliSourceComponent;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UChildActorComponent* WeaponComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Inventory")
	UInventoryComponent* Inventory;

#pragma region GameplayAbilitySystem
	
	UPROPERTY(EditDefaultsOnly)
	UAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY(EditDefaultsOnly)
	UBaseAttributeSet* AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	void InitializeDefaultAttributesAndEffects();

	TMap<FItemSlot, FGameplayAbilitySpecHandle> SlottedAbilities;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<EAbilities, TSubclassOf<UGameplayAbility>> StandardAbilities;

	void OnMovementSpeedChange(const FOnAttributeChangeData& Data);

public:	
	
	UFUNCTION()
	bool ActivateAbilitiesWithItemSlot(FItemSlot ItemSlot);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void RemoveSlottedGameplayAbilities(FItemSlot InSlot);

	UFUNCTION()
	void AddSlottedGameplayAbilities();

	UFUNCTION()
	void FillSlottedAbilitySpecs(TMap<FItemSlot, FGameplayAbilitySpec>& SlottedAbilitySpecs);

#pragma endregion 

	DECLARE_MULTICAST_DELEGATE_OneParam(FCharacterDeath, AGASBaseCharacter*);
	FCharacterDeath CharacterDeath;
	
	UFUNCTION(BlueprintCallable)
	void NotifyDeath();
	
	bool Attack();

	UInventoryComponent* GetInventoryComponent() const;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UChildActorComponent* GetWeaponComponent() const;
	
};
