// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolComponent.generated.h"


class ATargetPoint;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DREAMATETESTTASK_API UPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Patroling", Meta = (AllowPrivateAccess))
	TArray<ATargetPoint*> PatrolPoints;

public:
	UPatrolComponent();
	
	TArray<ATargetPoint*> GetPatrolPoints() const;
};
