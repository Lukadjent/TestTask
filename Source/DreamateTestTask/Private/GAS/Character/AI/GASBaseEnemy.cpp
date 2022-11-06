// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Character/AI/GASBaseEnemy.h"

#include "GameModeInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameModeBase.h"
#include "GAS/Ability/AbilitySet.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/FloatingBarWidget.h"

//Create widget component and set the variables of it
AGASBaseEnemy::AGASBaseEnemy()
{
	PatrolComponent = CreateDefaultSubobject<UPatrolComponent>("PatrolComponent");
	LootComponent = CreateDefaultSubobject<ULootComponent>("LootComponent");
}

void AGASBaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	IGameModeInterface* GameModeInterface = Cast<IGameModeInterface>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameModeInterface)
	{
		GameModeInterface->AddToEnemyArray();
		CharacterDeath.AddRaw(GameModeInterface, &IGameModeInterface::OnEnemyCharacterDeath);
		CharacterDeath.AddUObject(this, &AGASBaseEnemy::OnDeath);
	}
	if (AbilitySystemComponent && AbilitySet)
	{
		AbilitySet->GiveAbilities(AbilitySystemComponent);
	}
}

void AGASBaseEnemy::ImmobileTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_None);
		GetController()->StopMovement();
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
}

void AGASBaseEnemy::OnDeath()
{
	LootComponent->SpawnLoot();
	Destroy();
}

UPatrolComponent* AGASBaseEnemy::GetPatrolComponent() const
{
	return PatrolComponent.Get();
}
