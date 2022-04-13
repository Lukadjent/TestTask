// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/Service/BTService_FindPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UBTService_FindPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	if (UBlackboardComponent* Blackboard = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent()))
	{
		if (APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
		{
			Blackboard->SetValueAsObject("Player",PlayerPawn);
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
}
