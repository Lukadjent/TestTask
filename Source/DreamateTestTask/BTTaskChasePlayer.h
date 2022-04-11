// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API UBTTaskChasePlayer : public UBTTaskNode
{
	GENERATED_BODY()

	UBTTaskChasePlayer();
	
	 virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
