// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/MainGameMode.h"

void AMainGameMode::OnPlayerCharacterDeath() 
{
	Lose();
}

void AMainGameMode::OnEnemyCharacterDeath() 
{
	EnemyCounter--;
	if (EnemyCounter == 0)
	{
		Victory();
	}
}

void AMainGameMode::AddToEnemyArray()
{
	++EnemyCounter;
}
