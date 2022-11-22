// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GASCharacterComponent.generated.h"


struct FOnAttributeChangeData;
struct FGameplayTag;


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DREAMATETESTTASK_API UGASCharacterComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGASCharacterComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	void OnMovementSpeedChange(const FOnAttributeChangeData& Data);

	//On add or remove immobile tag
	void ImmobileTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
};
