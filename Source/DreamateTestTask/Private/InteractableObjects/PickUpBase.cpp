// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/PickUpBase.h"

#include "GAS/Character/AI/GASBaseCharacter.h"
#include "Inventory/InventoryComponent.h"

// Sets default values
APickUpBase::APickUpBase()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMeshComponent;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Collision");
	BoxComponent->SetupAttachment(StaticMeshComponent);
}

UObject* APickUpBase::OnInteraction()
{
	Destroy();
	return Item;
}