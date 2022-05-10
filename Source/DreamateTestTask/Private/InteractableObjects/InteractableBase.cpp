// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/InteractableBase.h"


// Sets default values
AInteractableBase::AInteractableBase()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = StaticMeshComponent;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractableBase::OnInteraction(AGASBaseCharacter* Character)
{
}


