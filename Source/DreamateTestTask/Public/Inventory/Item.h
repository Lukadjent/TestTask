// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Enum/EItemType.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class DREAMATETESTTASK_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	FString Name;

	FText Description;

	FTexture2DResource* Thumbnail;

	EItemType ItemType;

	int CurrentQuantity;
	
	int MaxQuantity;

	int GetCurrentQuantity() const {return CurrentQuantity;}
	
	void SetCurrentQuantity(int NewQuantity) {CurrentQuantity = (NewQuantity > MaxQuantity) ? MaxQuantity : NewQuantity;}
	
	FGameplayTag GrantedTag;
};
