// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Character/AI/GASBaseEnemy.h"
#include "GameModeInterface.h"
#include "Components/CharacterWidgetComponent.h"
#include "GAS/Ability/AbilitySet.h"
#include "Kismet/GameplayStatics.h"


//Create widget component and set the variables of it
AGASBaseEnemy::AGASBaseEnemy()
{
	PatrolComponent = CreateDefaultSubobject<UPatrolComponent>("PatrolComponent");
	LootComponent = CreateDefaultSubobject<ULootComponent>("LootComponent");
	WidgetComponent = CreateDefaultSubobject<UCharacterWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);
	AbilitySetComponent = CreateDefaultSubobject<UAbilitySetComponent>("AbilitySetComponent");
	GASCharacterComponent = CreateDefaultSubobject<UGASCharacterComponent>("GASCharacterComponent");
}

void AGASBaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

UPatrolComponent* AGASBaseEnemy::GetPatrolComponent() const
{
	return PatrolComponent.Get();
}
