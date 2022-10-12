// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainHUD.h"

#include "GameModeInterface.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerControllerInterface.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/LoseWidget.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	IGameModeInterface* GameMode = Cast<IGameModeInterface>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GameMode)
	{
		GameMode->OnLose.AddUObject(this, &AMainHUD::CreateLoseWidget);
		GameMode->OnVictory.AddUObject(this, &AMainHUD::CreateVictoryWidget);
	}
	
	MainHUDWidget = CreateWidget<UCharacterHUDWidget>(GetOwningPlayerController(), PlayerHUDClass);
	if (MainHUDWidget)
	{
		MainHUDWidget->AddToViewport();
	}

	IPlayerControllerInterface* PlayerController = Cast<IPlayerControllerInterface>(GetOwningPlayerController());
	if (PlayerController)
	{
		PlayerController->OpenInventoryActionDelegate.AddUObject(this, &AMainHUD::HandleInventory);
	}
}

void AMainHUD::HandleInventory()
{
	InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
	if (InventoryWidget)
	{
		InventoryWidget->AddToViewport();
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
