// Copyright Epic Games, Inc. All Rights Reserved.


#include "DreamateTestTask/Public/GAS/DreamateTestTaskGameModeBase.h"

void ADreamateTestTaskGameModeBase::Victory() const
{
	OnVictory.Broadcast();
}

void ADreamateTestTaskGameModeBase::Lose() const
{
	OnLose.Broadcast();
}
