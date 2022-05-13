// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "Inventory/Item/ItemData.h"
#include "PickUpBase.generated.h"

UCLASS()
class DREAMATETESTTASK_API APickUpBase : public AInteractableBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickUpBase();

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item")
	UItemData* Item;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item")
	int32 Amount = 1;
	
public:

	virtual void OnInteraction(AGASBaseCharacter* Character) override;
};
