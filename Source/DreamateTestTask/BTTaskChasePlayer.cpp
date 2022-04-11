// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskChasePlayer.h"

#include "EnemyController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tasks/AITask_MoveTo.h"

UBTTaskChasePlayer::UBTTaskChasePlayer()
{
	NodeName = "ChasePlayer";
}

EBTNodeResult::Type UBTTaskChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	NodeName = "ChasePlayer";
	AEnemyController* AIController = Cast<AEnemyController>(OwnerComp.GetOwner());
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AIController->MoveToActor(PlayerPawn);
	return AIController->GetPawn()->GetActorLocation().Equals(PlayerPawn->GetActorLocation(), 50.f) ? EBTNodeResult::InProgress : EBTNodeResult::Succeeded;
}
