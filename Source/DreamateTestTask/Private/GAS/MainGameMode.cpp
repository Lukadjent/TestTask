// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/MainGameMode.h"

#include "GameFramework/Character.h"
#include "Interfaces/Death.h"

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

void AMainGameMode::CharacterSpawn(ACharacter* Character)
{
	IDeath* DeathInterface = Cast<IDeath>(Character);
	if (DeathInterface)
	{
		if (Character->GetClass() == DefaultPawnClass)
		{
			DeathInterface->CharacterDeath.AddUObject(this, &AMainGameMode::OnPlayerCharacterDeath);
		}
		else
		{
			++EnemyCounter;
			DeathInterface->CharacterDeath.AddUObject(this, &AMainGameMode::OnEnemyCharacterDeath);
		}
	}
}

void AMainGameMode::Victory() const
{
	OnVictory.Broadcast();
}

void AMainGameMode::Lose() const
{
	OnLose.Broadcast();
}
