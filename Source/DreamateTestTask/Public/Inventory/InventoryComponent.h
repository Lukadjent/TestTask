// Fill out your copyright notice in the Description page of Project Settings.

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

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	FItemSlot EquippedWeapon;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TMap<UItemData*, FItemDataStruct> InventoryData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TMap<UItemData*, FItemDataStruct> DefaultInventory;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TMap<FItemSlot, UItemData*> SlottedItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TMap<FItemSlot, UItemData*> DefaultSlottedItems;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryItemChanged OnInventoryItemChanged;

	FOnInventoryItemChangedNative OnInventoryItemChangedNative;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnSlottedItemChanged OnSlottedItemChanged;

	FOnSlottedItemChangedNative OnSlottedItemChangedNative;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SlottedItemChanged(FItemSlot ItemSlot, UItemData* Item);

	UFUNCTION(BlueprintCallable)
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddInventoryItem(UItemData* NewItem, int32 ItemCount = 1);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveInventoryItem(UItemData* RemovedItem, int32 RemoveCount = 1);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void GetInventoryItemsOfType(TArray<UItemData*>& Items, FPrimaryAssetType InType);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetInventoryItemCount(UItemData* Item);

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

	UFUNCTION(BlueprintCallable)
	const TMap<UItemData*, FItemDataStruct>& GetInventoryDataMap() const;

	const TMap<FItemSlot, UItemData*>& GetSlottedItemMap() const;
};
