// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/Task/BTTaskChoosePatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GAS/Character/AI/EnemyController.h"
#include "GAS/Character/AI/GASBaseEnemy.h"

UBTTaskChoosePatrolPoint::UBTTaskChoosePatrolPoint()
{
	NodeName = "ChoosePoint";
}

EBTNodeResult::Type UBTTaskChoosePatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const AEnemyController* AIController = Cast<AEnemyController>(OwnerComp.GetOwner()))
	{
		if (const AGASBaseEnemy* Pawn = Cast<AGASBaseEnemy>(AIController->GetPawn()))
		{
			if (UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent())
			{
				int32 index = Pawn->PatrolPoints.IndexOfByKey(BlackboardComponent->GetValueAsObject("PatrolPoint"));
				index = (index + 1) % Pawn->PatrolPoints.Num();
				BlackboardComponent->SetValueAsObject("PatrolPoint", Pawn->PatrolPoints[index]);
				return Pawn->PatrolPoints[index] ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
			}
		}
	}
	return EBTNodeResult::Failed;
}
