// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASBaseCharacter.h"
#include "PatrolInterface.h"
#include "Inventory/LootComponent.h"
#include "UI/FloatingBarWidget.h"
#include "GASBaseEnemy.generated.h"

class UCharacterWidgetComponent;
class UAbilitySet;
/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API AGASBaseEnemy : public AGASBaseCharacter, public IPatrolInterface
{
	GENERATED_BODY()

	AGASBaseEnemy();

	virtual void BeginPlay() override;

#pragma region COMPONENTS

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patrol", Meta = (AllowPrivateAccess))
	TObjectPtr<UPatrolComponent> PatrolComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loop", Meta = (AllowPrivateAccess))
	TObjectPtr<ULootComponent> LootComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI", Meta = (AllowPrivateAccess))
	TObjectPtr<UCharacterWidgetComponent> WidgetComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAbilitySetComponent> AbilitySetComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UGASCharacterComponent> GASCharacterComponent;

#pragma endregion
public:

	virtual UPatrolComponent* GetPatrolComponent() const override;
	
};
