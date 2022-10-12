// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/Obelisk.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeInterface.h"
#include "Kismet/GameplayStatics.h"

AObelisk::AObelisk()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMeshComponent;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Collision");
	BoxComponent->SetupAttachment(StaticMeshComponent);
}

UObject* AObelisk::OnInteraction()
{
	IGameModeInterface* GameMode = Cast<IGameModeInterface>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->Victory();	
	}
	
	return nullptr;
}

