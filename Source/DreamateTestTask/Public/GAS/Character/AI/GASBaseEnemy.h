// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dummy.h"
#include "GASBaseCharacter.h"
#include "PatrolInterface.h"
#include "Inventory/LootComponent.h"
#include "UI/FloatingBarWidget.h"
#include "GASBaseEnemy.generated.h"

class UAbilitySet;
/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API AGASBaseEnemy : public ADummy, public IPatrolInterface
{
	GENERATED_BODY()

	AGASBaseEnemy();

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patrol", Meta = (AllowPrivateAccess))
	TObjectPtr<UPatrolComponent> PatrolComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patrol", Meta = (AllowPrivateAccess))
	TObjectPtr<ULootComponent> LootComponent;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const UAbilitySet* AbilitySet;
	
	//Override of the function that reacts on Immobile tag added/removed
	virtual void ImmobileTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;

	void OnDeath();
	
public:

	virtual UPatrolComponent* GetPatrolComponent() const override;
	
};
