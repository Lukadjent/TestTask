// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterHUDWidget.h"
#include "InventoryWidget.h"
#include "LoseWidget.h"
#include "VictoryWidget.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API AMainHUD : public AHUD
{
	GENERATED_BODY()

virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite)
    	TSoftObjectPtr<UCharacterHUDWidget> MainHUDWidget;
	

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> PlayerHUDClass;

#pragma region INVENTORY
	
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<UInventoryWidget> InventoryWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	void HandleInventory();

#pragma endregion 

#pragma region END_OF_THE_GAME

	UPROPERTY()
	TSoftObjectPtr<UVictoryWidget> VictoryWidget;

	UPROPERTY()
	TSoftObjectPtr<ULoseWidget> LoseWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> VictoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> LoseWidgetClass;

	void CreateVictoryWidget();

	void CreateLoseWidget();
#pragma endregion 
};
