// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/Task/BTTaskChoosePatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/TargetPoint.h"
#include "GAS/Character/AI/PatrolComponent.h"
#include "GAS/Character/AI/PatrolInterface.h"

UBTTaskChoosePatrolPoint::UBTTaskChoosePatrolPoint()
{
	NodeName = "ChoosePoint";
}

EBTNodeResult::Type UBTTaskChoosePatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	check(OwnerComp.GetBlackboardComponent());
	if (const IPatrolInterface* PatrolInterface = Cast<IPatrolInterface>(Cast<AController>(OwnerComp.GetOwner())->GetPawn()))
	{
		if (!PatrolInterface->GetPatrolComponent()->GetPatrolPoints().IsEmpty())
		{
			int32 index = PatrolInterface->GetPatrolComponent()->GetPatrolPoints().IndexOfByKey(OwnerComp.GetBlackboardComponent()->GetValueAsObject("PatrolPoint"));
			index = (index + 1) % PatrolInterface->GetPatrolComponent()->GetPatrolPoints().Num();
			OwnerComp.GetBlackboardComponent()->SetValueAsObject("PatrolPoint", PatrolInterface->GetPatrolComponent()->GetPatrolPoints()[index]);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
