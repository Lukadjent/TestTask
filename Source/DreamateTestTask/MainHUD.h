// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Public/UI/CharacterHUDWidget.h"
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
	UCharacterHUDWidget* MainHUDWidget;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class UUserWidget> PlayerHUDClass;	
};
