// Copyright Epic Games, Inc. All Rights Reserved.


#include "DreamateTestTask/Public/GAS/DreamateTestTaskGameModeBase.h"
#include "Kismet/GameplayStatics.h"


void ADreamateTestTaskGameModeBase::OnPlayerCharacterDeath() 
{
	PlayAgainWidget = CreateWidget<UPlayAgainWidget>(GetWorld(), WidgetClass);
	if (PlayAgainWidget)
	{
		PlayAgainWidget->SetText("You Died");
		PlayAgainWidget->AddToViewport();
	}
}

void ADreamateTestTaskGameModeBase::OnEnemyCharacterDeath() 
{
	EnemyCounter--;
	if (EnemyCounter == 0)
	{
		Victory();
	}
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("Enemy Died, %d left."), EnemyCounter));
}

void ADreamateTestTaskGameModeBase::AddToEnemyArray()
{
	++EnemyCounter;
}

void ADreamateTestTaskGameModeBase::Victory()
{
	PlayAgainWidget = CreateWidget<UPlayAgainWidget>(GetWorld(), WidgetClass);
	if (PlayAgainWidget)
	{
		PlayAgainWidget->SetText("You Won");
		PlayAgainWidget->AddToViewport();
	}
}
