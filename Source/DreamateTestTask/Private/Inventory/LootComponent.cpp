// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/LootComponent.h"
#include "Interfaces/Death.h"
#include "Kismet/KismetMathLibrary.h"


ULootComponent::ULootComponent()
{
	
}

void ULootComponent::BeginPlay()
{
	Super::BeginPlay();

	IDeath* DeathInterface = Cast<IDeath>(GetOwner());
	if (DeathInterface)
	{
		DeathInterface->CharacterDeath.AddUObject(this, &ULootComponent::SpawnLoot);
	}
}

void ULootComponent::SpawnLoot() const
{
	if (!Drop.IsEmpty())
	{
		if (UKismetMathLibrary::RandomBoolWithWeight(DropProbability))
		{
			const TSubclassOf<APickUpBase> Class = Drop[FMath::RandRange(0, Drop.Num() - 1)];
			const FVector SpawnLocation = GetOwner()->GetActorLocation() - FVector(0.f,0.f, 80.f);
			GetWorld()->SpawnActor(Class, &SpawnLocation);	
		}
	}	
}

