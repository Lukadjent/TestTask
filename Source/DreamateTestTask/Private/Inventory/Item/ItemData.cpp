// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/Item/ItemData.h"

bool UItemData::IsConsumable() const
{
	return MaxCount <= 1 ? false : true;
}

FString UItemData::GetIdentifierString() const
{
	return GetPrimaryAssetId().ToString();
}

FPrimaryAssetId UItemData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(ItemType, FName());
}
