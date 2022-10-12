// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "Components/BoxComponent.h"
#include "Inventory/Item/ItemData.h"
#include "PickUpBase.generated.h"

UCLASS()
class DREAMATETESTTASK_API APickUpBase : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "StaticMeshComponent", meta = (AllowPrivateAccess))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BoxComponent", meta = (AllowPrivateAccess))
	UBoxComponent* BoxComponent;
	
public:
	// Sets default values for this actor's properties
	APickUpBase();

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item")
	UItemData* Item;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item")
	int32 Amount = 1;
	
public:

	//virtual void OnInteraction(AGASBaseCharacter* Character) override;
	virtual UObject* OnInteraction() override;
};
