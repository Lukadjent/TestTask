// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "DreamateTestTask/Public/GAS/Character/AI/GASBaseCharacter.h"
#include "Components/ActorComponent.h"
#include "Consumable/Consumable.h"
#include "Weapon/Weapon.h"
#include "InventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DREAMATETESTTASK_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TMap<TSubclassOf<AItem>, int> Inventory;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory|Default")
	TMap<TSubclassOf<AItem>, int> DefaultSlots;

	TSubclassOf<AWeapon> EquippedWeapon;

	TSubclassOf<AConsumable> EquippedConsumable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory|Default")
	TSubclassOf<AWeapon> DefaultEquippedWeapon;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory|Default")
	TSubclassOf<AConsumable> DefaultEquippedConsumable;
	
	
	void AddDefaults();

	void Initialize();
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(TSubclassOf<AWeapon> Weapon);

	void EquipConsumable(TSubclassOf<AConsumable> Consumable);

	void Unequip(TSubclassOf<AItem> Item);
	
	void AddItem(TSubclassOf<AItem> Item, int Quantity);

	void SwitchWeapon(const EWeaponType NewWeapon) const;

	UPROPERTY()
	AGASBaseCharacter* Owner;

	TTuple<TSubclassOf<AConsumable>, int> GetEquippedConsumable() const;
	
};
