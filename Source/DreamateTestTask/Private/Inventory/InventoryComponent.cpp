// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/InventoryComponent.h"

#include "GAS/Character/AI/GASBaseCharacter.h"
#include "Inventory/Item/ItemAssetManager.h"
#include "Inventory/Item/WeaponItemData.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::SlottedItemChanged(FItemSlot ItemSlot, UItemData* Item)
{
	if (UChildActorComponent* Weapon = GetOwner()->FindComponentByClass<UChildActorComponent>())
	{
		if (ItemSlot.GetItemType() == UItemAssetManager::WeaponItemType)
		{
			if (const UWeaponItemData* WeaponData = Cast<UWeaponItemData>(Item))
			{
				Weapon->SetChildActorClass(WeaponData->GetWeaponClass());	
			}
		}
	}
}

bool UInventoryComponent::AddInventoryItem(UItemData* NewItem, int32 ItemCount, bool bAutoSlot)
{
	if (!NewItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::AddInventoryItem: Failed to add null item!"));
		return false;
	}
	if (ItemCount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::AddInventoryItem: Failed trying to add %s with negaive ItemCount!"), *NewItem->GetName());
		return false;
	}
	bool bChanged = false;
	FItemDataStruct OldData;
	GetInventoryItemData(NewItem, OldData);
	FItemDataStruct NewData = OldData;
	NewData.UpdateItemData(FItemDataStruct(ItemCount), NewItem->MaxCount);

	if (OldData != NewData)
	{
		InventoryData.Add(NewItem, NewData);
		NotifyInventoryItemChanged(true, NewItem);
		bChanged = true;
	}
	return bChanged;
}

bool UInventoryComponent::RemoveInventoryItem(UItemData* RemovedItem, int32 RemoveCount)
{
	if (!RemovedItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::RemoveInventoryItem: Failed to remove null item!"));
		return false;
	}
	FItemDataStruct NewData;
	GetInventoryItemData(RemovedItem, NewData);
	if (!NewData.IsValid())
	{
		UE_LOG(LogTemp, Display, TEXT("UInventoryComponent::RemoveInventoryItem: Failed to find %s!"), *RemovedItem->GetName());
		return false;
	}
	if (RemoveCount <= 0)
	{
		NewData.ItemCount = 0;
	}
	else
	{
		NewData.ItemCount -= RemoveCount;
	}
	if (NewData.ItemCount > 0)
	{
		InventoryData.Add(RemovedItem, NewData);
	}
	else
	{
		InventoryData.Remove(RemovedItem);
		for (TPair<FItemSlot, UItemData*> Slot : SlottedItems)
		{
			if (Slot.Value == RemovedItem)
			{
				Slot.Value = nullptr;
				NotifySlottedItemChanged(Slot.Key, Slot.Value);
			}
		}
	}
	NotifyInventoryItemChanged(false, RemovedItem);
	return true;
}

void UInventoryComponent::GetInventoryItemsOfType(TArray<UItemData*>& Items, FPrimaryAssetType InType)
{
	for (const TPair<UItemData*, FItemDataStruct>& Pair : InventoryData)
	{
		if (Pair.Key)
		{
			FPrimaryAssetId AssetId = Pair.Key->GetPrimaryAssetId();

			if (AssetId.PrimaryAssetType == InType || !InType.IsValid())
			{
				Items.Add(Pair.Key);
			}
		}
	}
}

int32 UInventoryComponent::GetInventoryItemCount(UItemData* Item)
{
	const FItemDataStruct* FoundItem = InventoryData.Find(Item);
	if (FoundItem)
	{
		return FoundItem->ItemCount;
	}
	return 0;
}

bool UInventoryComponent::GetInventoryItemData(UItemData* Item, FItemDataStruct ItemData) const
{
	if (const FItemDataStruct* FoundItem = InventoryData.Find(Item))
	{
		ItemData = *FoundItem;
		return true;
	}
	ItemData = FItemDataStruct(0);
	return false;
}

bool UInventoryComponent::SetSlottedItem(FItemSlot Slot, UItemData* Item)
{
	bool bFound = false;
	for (TPair<FItemSlot, UItemData*>& Pair : SlottedItems)
	{
		if (Pair.Key == Slot)
		{
			bFound = true;
			Pair.Value = Item;
			NotifySlottedItemChanged(Pair.Key, Pair.Value);
		}
		else if (Item && Pair.Value == Item)
		{
			Pair.Value = nullptr;
			NotifySlottedItemChanged(Pair.Key, Pair.Value);
		}
	}
	return bFound;
}

UItemData* UInventoryComponent::GetSlottedItem(FItemSlot Slot)
{
	if (UItemData* const* FoundItem = SlottedItems.Find(Slot))
	{
		return *FoundItem;
	}
	return nullptr;
}

void UInventoryComponent::GetSlottedItems(TArray<UItemData*>& Items, FPrimaryAssetType Type, bool bOutputEmptyIndexes)
{
	for (TPair<FItemSlot, UItemData*>& Pair : SlottedItems)
	{
		if (Pair.Key.ItemType == Type || !Type.IsValid())
		{
			Items.Add(Pair.Value);
		}
	}
}

void UInventoryComponent::FillEmptySlots()
{
	
}

const TMap<UItemData*, FItemDataStruct>& UInventoryComponent::GetInventoryDataMap() const
{
	return InventoryData;
}

const TMap<FItemSlot, UItemData*>& UInventoryComponent::GetSlottedItemMap() const
{
	return SlottedItems;
}

void UInventoryComponent::NotifyInventoryItemChanged(bool bAdded, UItemData* Item)
{
	OnInventoryItemChanged.Broadcast(bAdded, Item);
	OnInventoryItemChangedNative.Broadcast(bAdded, Item);

	InventoryItemChanged(bAdded, Item);
}

void UInventoryComponent::NotifySlottedItemChanged(FItemSlot Slot, UItemData* Item)
{
	OnSlottedItemChanged.Broadcast(Slot, Item);
	OnSlottedItemChangedNative.Broadcast(Slot, Item);

	SlottedItemChanged(Slot, Item);
}
