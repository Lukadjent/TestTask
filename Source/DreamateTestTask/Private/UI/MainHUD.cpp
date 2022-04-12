// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainHUD.h"
#include "Blueprint/UserWidget.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	MainHUDWidget = CreateWidget<UCharacterHUDWidget>(GetWorld(), PlayerHUDClass);
	if (MainHUDWidget)
	{
		MainHUDWidget->AddToViewport();
	}
}
