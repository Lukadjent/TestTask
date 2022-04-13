// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/Task/BTTaskAttack.h"
#include "Enum/EAbilities.h"
#include "GAS/Character/AI/EnemyController.h"
#include "GAS/Character/AI/GASBaseEnemy.h"

UBTTaskAttack::UBTTaskAttack()
{
	NodeName = "Attack";
}

EBTNodeResult::Type UBTTaskAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const AEnemyController* AIController = Cast<AEnemyController>(OwnerComp.GetOwner()))
	{
		if (const AGASBaseEnemy* Pawn = Cast<AGASBaseEnemy>(AIController->GetPawn()))
		{
			if (Pawn->GetAbilitySystemComponent()->TryActivateAbilityByClass(Pawn->StandardAbilities[EAbilities::Attack]))
			{
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
