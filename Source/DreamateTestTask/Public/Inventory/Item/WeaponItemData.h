// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "Inventory/Item/ItemData.h"
#include "DreamateTestTask/Public/Inventory/Weapon/Weapon.h"
#include "WeaponItemData.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API UWeaponItemData : public UItemData
{
	GENERATED_BODY()

	UWeaponItemData();

public:
	
	TSubclassOf<AWeapon> GetWeaponClass() const
	{
		return WeaponActor;
	}
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<AWeapon> WeaponActor; 
	
};
