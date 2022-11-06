// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/Task/BTTaskAttack.h"

#include "DreamateBlueprintFunctionLibrary.h"
#include "GameplayTagsManager.h"
#include "GAS/Character/AI/GASAIController.h"
#include "GAS/Character/AI/GASBaseEnemy.h"

UBTTaskAttack::UBTTaskAttack()
{
	NodeName = "Attack";
}

EBTNodeResult::Type UBTTaskAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController =UDreamateBlueprintFunctionLibrary::GetAIController(OwnerComp.GetOwner());
	if (AIController->GetPawn())
	{
		const IAbilitySystemComponentInterface* ASCInterface = Cast<IAbilitySystemComponentInterface>(AIController->GetPawn());
		if (ASCInterface)
		{
			UASComponent* ASC = ASCInterface->GetAbilitySystemComponent();
			if (ASC)
			{
				const FGameplayTag AttackTag = FGameplayTag::RequestGameplayTag(FName("Ability.Active.Attack"));
				if (ASC->TryActivateAbilitiesByTag(FGameplayTagContainer(AttackTag)))
				{
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
