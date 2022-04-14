// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/Item/WeaponItemData.h"
#include "Inventory/Item/ItemAssetManager.h"

UWeaponItemData::UWeaponItemData()
{
	ItemType = UItemAssetManager::WeaponItemType;
}
