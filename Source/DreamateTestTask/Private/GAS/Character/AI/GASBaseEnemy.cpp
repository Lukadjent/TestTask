// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Character/AI/GASBaseEnemy.h"

#include "CharacterDeathHandleInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/FloatingBarWidget.h"

//Create widget component and set the variables of it
AGASBaseEnemy::AGASBaseEnemy()
{
	
}

void AGASBaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	ICharacterDeathHandleInterface* CharacterDeathHandleInterface = Cast<ICharacterDeathHandleInterface>(UGameplayStatics::GetGameMode(GetWorld()));
	if (CharacterDeathHandleInterface)
	{
		CharacterDeathHandleInterface->AddToEnemyArray();
		CharacterDeath.AddRaw(CharacterDeathHandleInterface, &ICharacterDeathHandleInterface::OnEnemyCharacterDeath);
		CharacterDeath.AddUObject(this, &AGASBaseEnemy::OnDeath);
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
	SpawnLoot();
	Destroy();
}

TArray<ATargetPoint*> AGASBaseEnemy::GetPatrolPoints() const
{
	return PatrolPoints;
}

void AGASBaseEnemy::SpawnLoot()
{
	if (!Drop.IsEmpty())
	{
		if (UKismetMathLibrary::RandomBoolWithWeight(DropProbability))
		{
			const TSubclassOf<APickUpBase> Class = Drop[FMath::RandRange(0, Drop.Num() - 1)];
			const FVector SpawnLocation = GetActorLocation() - FVector(0.f,0.f, 80.f);
			GetWorld()->SpawnActor(Class, &SpawnLocation);	
		}
	}
}
