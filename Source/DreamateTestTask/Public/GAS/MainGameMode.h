// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/DreamateTestTaskGameModeBase.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API AMainGameMode : public ADreamateTestTaskGameModeBase, public ICharacterDeathHandleInterface
{
	GENERATED_BODY()

	virtual void OnPlayerCharacterDeath()  override;

	virtual void OnEnemyCharacterDeath()  override;

	virtual void AddToEnemyArray() override;

	int32 EnemyCounter;
};
