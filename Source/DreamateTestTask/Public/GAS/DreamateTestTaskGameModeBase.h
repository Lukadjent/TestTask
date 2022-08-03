// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterDeathHandleInterface.h"
#include "GameFramework/GameModeBase.h"
#include "UI/PlayAgainWidget.h"
#include "DreamateTestTaskGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API ADreamateTestTaskGameModeBase : public AGameModeBase, public ICharacterDeathHandleInterface
{
	GENERATED_BODY()

	virtual void OnPlayerCharacterDeath()  override;

	virtual void OnEnemyCharacterDeath()  override;

	virtual void AddToEnemyArray() override;

	//
	UPROPERTY()
	UPlayAgainWidget* PlayAgainWidget;


protected:

	int32 EnemyCounter;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UPlayAgainWidget> WidgetClass;
	
public:

	void Victory();
};
