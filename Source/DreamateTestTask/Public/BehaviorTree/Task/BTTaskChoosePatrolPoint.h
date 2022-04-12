// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskChoosePatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API UBTTaskChoosePatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()

	UBTTaskChoosePatrolPoint();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
