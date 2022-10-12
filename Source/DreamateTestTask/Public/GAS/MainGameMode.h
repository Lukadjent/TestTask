// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeInterface.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API AMainGameMode : public AGameModeBase, public IGameModeInterface
{
	GENERATED_BODY()

	virtual void OnPlayerCharacterDeath()  override;

	virtual void OnEnemyCharacterDeath()  override;

	virtual void AddToEnemyArray() override;
	
	virtual void Victory() const override;
	
	virtual void Lose() const override;

	int32 EnemyCounter;
};
