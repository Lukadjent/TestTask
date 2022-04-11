// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskChoosePatrolPoint.h"

#include "EnemyController.h"
#include "GASBaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskChoosePatrolPoint::UBTTaskChoosePatrolPoint()
{
	NodeName = "ChoosePoint";
}

EBTNodeResult::Type UBTTaskChoosePatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AEnemyController* AIController = Cast<AEnemyController>(OwnerComp.GetOwner());
	const AGASBaseEnemy* Pawn = Cast<AGASBaseEnemy>(AIController->GetPawn());
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	int32 index = Pawn->PatrolPoints.IndexOfByKey(BlackboardComponent->GetValueAsObject("PatrolPoint"));
	index = (index + 1) % Pawn->PatrolPoints.Num();
	/*if (index = Pawn->PatrolPoints.Num() - 1)
	{
		index = 0;
	}
	else
	{
		++index;
	}*/
	BlackboardComponent->SetValueAsObject("PatrolPoint", Pawn->PatrolPoints[index]);
	BlackboardComponent->SetValueAsVector("Location", Pawn->PatrolPoints[index]->GetActorLocation());
	return Pawn->PatrolPoints[index] ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
