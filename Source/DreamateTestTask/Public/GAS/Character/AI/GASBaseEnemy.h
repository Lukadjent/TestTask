// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASBaseCharacter.h"
#include "Components/WidgetComponent.h"
#include "Engine/TargetPoint.h"
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

#pragma endregion

	FDelegateHandle HealthChangedDelegateHandle;

	void HealthChanged(const FOnAttributeChangeData& Data);
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Patroling")
	TArray<ATargetPoint*> PatrolPoints;

	
};
