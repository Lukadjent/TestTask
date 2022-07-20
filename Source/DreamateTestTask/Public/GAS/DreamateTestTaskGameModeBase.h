// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/AI/GASBaseEnemy.h"
#include "Character/Player/GASMainCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "UI/PlayAgainWidget.h"
#include "DreamateTestTaskGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API ADreamateTestTaskGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	
	UPROPERTY()
	TArray<AGASBaseCharacter*> Enemies;

	UPROPERTY()
	AGASMainCharacter* PlayerCharacter = nullptr;
	
	void OnEnemyDeath(AGASBaseCharacter* Enemy);

	void OnPlayerCharacterDeath(AGASBaseCharacter* Character);


	//
	UPROPERTY()
	UPlayAgainWidget* PlayAgainWidget;

protected:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UPlayAgainWidget> WidgetClass;
	
public:

	void Victory();
};
