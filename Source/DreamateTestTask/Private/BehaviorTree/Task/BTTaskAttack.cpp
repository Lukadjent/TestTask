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
	APawn* Pawn = Cast<AGASBaseEnemy>(Cast<AGASAIController>(OwnerComp.GetOwner())->GetPawn());
	const IAbilitySystemComponentInterface* ASCInterface = Cast<IAbilitySystemComponentInterface>(Pawn);
	if (ASCInterface)
	{
		UASComponent* ASC = ASCInterface->GetAbilitySystemComponent();
		if (ASC)
		{
			if (ASC->Attack())
			{
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
