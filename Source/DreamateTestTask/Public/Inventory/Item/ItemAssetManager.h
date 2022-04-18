// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "ItemAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API UItemAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	
	static const FPrimaryAssetType WeaponItemType;
	static const FPrimaryAssetType PotionItemType;
	static const FPrimaryAssetType None;
};
