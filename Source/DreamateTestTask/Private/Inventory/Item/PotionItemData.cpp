// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/PotionItemData.h"

#include "Inventory/Item/ItemAssetManager.h"

UPotionItemData::UPotionItemData()
{
	ItemType = UItemAssetManager::PotionItemType;
}
