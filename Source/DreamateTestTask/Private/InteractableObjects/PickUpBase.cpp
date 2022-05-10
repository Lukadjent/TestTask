// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/PickUpBase.h"

#include "GAS/Character/AI/GASBaseCharacter.h"
#include "Inventory/InventoryComponent.h"

// Sets default values
APickUpBase::APickUpBase()
{

}

void APickUpBase::OnInteraction(AGASBaseCharacter* Character)
{
	Character->GetInventoryComponent()->AddInventoryItem(Item, Amount);
	Destroy();
}

