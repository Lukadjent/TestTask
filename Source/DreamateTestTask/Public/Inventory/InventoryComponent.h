
#pragma once

#include "CoreMinimal.h"
#include "InventoryTypes.h"
#include "Components/ActorComponent.h"
#include "EnvironmentQuery/EnvQueryDebugHelpers.h"
#include "Item/ItemData.h"
#include "InventoryComponent.generated.h"

class AGASBaseCharacter;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DREAMATETESTTASK_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
	
	FItemSlot EquippedWeapon;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//All the items in inventory
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TMap<UItemData*, FItemDataStruct> InventoryData;

	//Items in inventory available by default
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", Meta = (ExposeOnSpawn))
	TMap<UItemData*, FItemDataStruct> DefaultInventory;

	//Slotted Items
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TMap<FItemSlot, UItemData*> SlottedItems;

	//Slotted Items by default
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", Meta = (ExposeOnSpawn))
	TMap<FItemSlot, UItemData*> DefaultSlottedItems;

	//Delegates when inventory item changes
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryItemChanged OnInventoryItemChanged;
	
	FOnInventoryItemChangedNative OnInventoryItemChangedNative;

	//Delegates when slotted item changes
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnSlottedItemChanged OnSlottedItemChanged;

	FOnSlottedItemChangedNative OnSlottedItemChangedNative;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SlottedItemChanged(FItemSlot ItemSlot, UItemData* Item);

	//Give default items
	UFUNCTION(BlueprintCallable)
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveInventoryItem(UItemData* RemovedItem, int32 RemoveCount = 1);

	//Get all items of type
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void GetInventoryItemsOfType(TArray<UItemData*>& Items, FPrimaryAssetType InType);

	//Get amount of item in inventory
	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetInventoryItemCount(UItemData* Item);

	//Get inventory
	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool GetInventoryItemData(UItemData* Item, FItemDataStruct& ItemData) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool SetSlottedItem(FItemSlot Slot, UItemData* Item);
	
	UFUNCTION(BlueprintPure, Category = "Inventory")
	UItemData* GetSlottedItem(FItemSlot Slot);
	
	void NotifySlottedItemChanged(FItemSlot Slot, UItemData* Item);

	UPROPERTY()
	AGASBaseCharacter* Owner = nullptr;

public:	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddInventoryItem(UItemData* NewItem, int32 ItemCount = 1);
	
	UFUNCTION(BlueprintCallable)
	const TMap<UItemData*, FItemDataStruct>& GetInventoryDataMap() const;

	const TMap<FItemSlot, UItemData*>& GetSlottedItemMap() const;
};
