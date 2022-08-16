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

DECLARE_MULTICAST_DELEGATE(FVictoryDelegate)
DECLARE_MULTICAST_DELEGATE(FLoseDelegate)


UCLASS()
class DREAMATETESTTASK_API ADreamateTestTaskGameModeBase : public AGameModeBase
{
	GENERATED_BODY()	
	
public:

	FVictoryDelegate OnVictory;

	FLoseDelegate OnLose;
	
	void Victory() const;

	void Lose() const;
};
