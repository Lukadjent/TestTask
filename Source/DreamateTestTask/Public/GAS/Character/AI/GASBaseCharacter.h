// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UInventoryComponent;

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Enum/EAbilities.h"
#include "Enum/EWeaponType.h"
#include "GameFramework/Character.h"
#include "GAS/AttributeSet/BaseAttributeSet.h"
#include "Inventory/InventoryComponent.h"
#include "Inventory/InventoryTypes.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "GASBaseCharacter.generated.h"

UCLASS()
class DREAMATETESTTASK_API AGASBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Perception")
	UAIPerceptionStimuliSourceComponent* StimuliSourceComponent;
	
public:

	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UChildActorComponent* WeaponComponent;
	
	// Sets default values for this character's properties
	AGASBaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
	TMap<FItemSlot, TSubclassOf<UGameplayAbility>> DefaultSlottedAbilities;
	
public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> SetDamageGameplayEffect;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class UGameplayEffect> DefaultAttributes;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<EAbilities, TSubclassOf<UGameplayAbility>> StandardAbilities;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EWeaponType Weapon;

	UFUNCTION()
	bool ActivateAbilitiesWithItemSlot(FItemSlot ItemSlot);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void RemoveSlottedGameplayAbilities(FItemSlot InSlot);

	UFUNCTION()
	void AddSlottedGameplayAbilites();

	UFUNCTION()
	void FillSlottedAbilitySpecs(TMap<FItemSlot, FGameplayAbilitySpec>& SlottedAbilitySpecs);

#pragma endregion 
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void Attack();
	
};
