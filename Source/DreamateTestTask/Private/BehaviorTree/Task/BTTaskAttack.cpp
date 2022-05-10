// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/Task/BTTaskAttack.h"
#include "GAS/Character/AI/GASAIController.h"
#include "GAS/Character/AI/GASBaseEnemy.h"

UBTTaskAttack::UBTTaskAttack()
{
	NodeName = "Attack";
}

EBTNodeResult::Type UBTTaskAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AGASBaseEnemy* Pawn = Cast<AGASBaseEnemy>(Cast<AGASAIController>(OwnerComp.GetOwner())->GetPawn()))
	{
		if (Pawn->Attack())
		{
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
