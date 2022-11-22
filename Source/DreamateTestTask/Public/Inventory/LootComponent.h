// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableObjects/PickUpBase.h"
#include "LootComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DREAMATETESTTASK_API ULootComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULootComponent();

	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drop")
	TArray<TSubclassOf<APickUpBase>> Drop;

	//Should be a value from 0.0 to 1.0
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drop")
	float DropProbability;

public:
	void SpawnLoot() const;
};
