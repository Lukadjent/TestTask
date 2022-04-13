// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskAttack.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API UBTTaskAttack : public UBTTaskNode
{
	GENERATED_BODY()

	UBTTaskAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
