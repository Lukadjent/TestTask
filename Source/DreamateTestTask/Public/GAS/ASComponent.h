// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Enum/EAbilities.h"
#include "Inventory/InventoryTypes.h"
#include "UI/AttributesWidgetInterface.h"
#include "ASComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DREAMATETESTTASK_API UASComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UASComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TMap<EAbilities, TSubclassOf<UGameplayAbility>> DefaultAbilities;

	TMap<FItemSlot, FGameplayAbilitySpecHandle> SlottedAbilities;
	
public:

#pragma region ABILITIES
	bool Roll();
	bool Parry();
	bool CastSpell();
	bool UseConsumable();
	bool Attack();
#pragma endregion

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

	void BindAttributeToWidget(FGameplayAttribute Attribute, FGameplayAttribute AttributeMax, TScriptInterface<IAttributesWidgetInterface> Widget) const;
	
};
