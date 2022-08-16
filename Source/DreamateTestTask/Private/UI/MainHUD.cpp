// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainHUD.h"
#include "Blueprint/UserWidget.h"
#include "GAS/DreamateTestTaskGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	ADreamateTestTaskGameModeBase* GameMode = Cast<ADreamateTestTaskGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GameMode)
	{
		GameMode->OnLose.AddUObject(this, &AMainHUD::CreateLoseWidget);
		GameMode->OnVictory.AddUObject(this, &AMainHUD::CreateVictoryWidget);
	}
	
	MainHUDWidget = CreateWidget<UCharacterHUDWidget>(GetWorld(), PlayerHUDClass);
	if (MainHUDWidget)
	{
		MainHUDWidget->AddToViewport();
	}
}

void AMainHUD::CreateVictoryWidget()
{
	VictoryWidget = CreateWidget<UVictoryWidget>(GetWorld(), VictoryWidgetClass);
	if (VictoryWidget)
	{
		VictoryWidget->AddToViewport();
	}
}

void AMainHUD::CreateLoseWidget()
{
	LoseWidget = CreateWidget<ULoseWidget>(GetWorld(), LoseWidgetClass);
	if (LoseWidget)
	{
		LoseWidget->AddToViewport();
	}
}
