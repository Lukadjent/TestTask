// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemAssetManager.h"
#include "Item/ItemData.h"
#include "InventoryTypes.generated.h"

USTRUCT(BlueprintType)
struct DREAMATETESTTASK_API FItemSlot
{
	GENERATED_BODY();

	FItemSlot()
		:ItemType(UItemAssetManager::None)
	{}
	
	FItemSlot(const FPrimaryAssetType& InItemType)
		: ItemType(InItemType)
	{}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")	
	FPrimaryAssetType ItemType;

	FPrimaryAssetType GetItemType()
	{
		return ItemType;
	}
	
	bool operator==(const FItemSlot& Other) const 
	{
		return ItemType == Other.ItemType;
	}

	bool operator !=(const FItemSlot& Other) const
	{
		return !(*this == Other); 
	}

	bool IsValid() const
	{
		return ItemType.IsValid();
	}

	friend inline uint32 GetTypeHash(const FItemSlot& Key)
	{
		uint32 Hash = 0;
		Hash = HashCombine(Hash, GetTypeHash(Key.ItemType));
		return Hash;
	}
};

USTRUCT(BlueprintType)
struct DREAMATETESTTASK_API FItemDataStruct
{
	GENERATED_BODY();
	FItemDataStruct() : ItemCount(1) {}
	
	FItemDataStruct(int32 InItemCount) : ItemCount(InItemCount) {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ItemCount;

	bool operator==(const FItemDataStruct& Other) const
	{
		return ItemCount == Other.ItemCount;
	}

	bool operator!=(const FItemDataStruct& Other) const
	{
		return !(*this == Other);
	}

	bool IsValid() const
	{
		return ItemCount > 0;
	}
	
	void UpdateItemData(const FItemDataStruct& Other, int32 MaxCount)
	{
		MaxCount = MaxCount<=0 ? MAX_int32 : MaxCount;
		ItemCount = FMath::Clamp(ItemCount + Other.ItemCount, 1.f, MaxCount);
	}
};

/** Delegate called when an inventory item changes */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChanged, bool, bAdded, UItemData*, Item);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChangedNative, bool, UItemData*);

/** Delegate called when the contents of an inventory slot change */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlottedItemChanged, FItemSlot, ItemSlot, UItemData*, Item);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSlottedItemChangedNative, FItemSlot, UItemData*);
