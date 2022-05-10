// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/Task/BTTaskChoosePatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GAS/Character/AI/GASAIController.h"
#include "GAS/Character/AI/GASBaseEnemy.h"

UBTTaskChoosePatrolPoint::UBTTaskChoosePatrolPoint()
{
	NodeName = "ChoosePoint";
}

EBTNodeResult::Type UBTTaskChoosePatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const AGASBaseEnemy* Pawn = Cast<AGASBaseEnemy>(Cast<AGASAIController>(OwnerComp.GetOwner())->GetPawn()))
	{
		if (UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent())
		{
			if (!Pawn->GetPatrolPoints().IsEmpty())
			{
				int32 index = Pawn->GetPatrolPoints().IndexOfByKey(BlackboardComponent->GetValueAsObject("PatrolPoint"));
				index = (index + 1) % Pawn->GetPatrolPoints().Num();
				BlackboardComponent->SetValueAsObject("PatrolPoint", Pawn->GetPatrolPoints()[index]);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
