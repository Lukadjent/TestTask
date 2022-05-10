// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASBaseCharacter.h"
#include "Components/WidgetComponent.h"
#include "Engine/TargetPoint.h"
#include "InteractableObjects/PickUpBase.h"
#include "UI/FloatingBarWidget.h"
#include "GASBaseEnemy.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API AGASBaseEnemy : public AGASBaseCharacter
{
	GENERATED_BODY()

	AGASBaseEnemy();

	virtual void BeginPlay() override;

protected:

#pragma region UI
	
	UPROPERTY()
	UFloatingBarWidget* FloatingBarWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI|Bar")
	TSubclassOf<UFloatingBarWidget> FloatingBarClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	UWidgetComponent* WidgetComponent;

	FDelegateHandle HealthChangedDelegateHandle;

	void HealthChanged(const FOnAttributeChangeData& Data);

#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drop")
	TArray<TSubclassOf<APickUpBase>> Drop;

	//Should be a value from 0.0 to 1.0
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drop")
	float DropProbability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Patroling")
	TArray<ATargetPoint*> PatrolPoints;
	
public:

	TArray<ATargetPoint*> GetPatrolPoints() const;
	
	void SpawnLoot();
	
};
