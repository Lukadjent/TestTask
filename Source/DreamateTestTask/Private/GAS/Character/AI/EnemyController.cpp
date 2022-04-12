// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Character/AI/EnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GAS/Character/Player/GASMainCharacter.h"
#include "Perception/AIPerceptionComponent.h"

AEnemyController::AEnemyController()
{
	AAIController::SetGenericTeamId(FGenericTeamId(1));
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = SightRange;
	SightConfig->LoseSightRadius = LoseSightRange;
	SightConfig->PeripheralVisionAngleDegrees = SightAngle;
	SightConfig->SetMaxAge(MaxAge);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = bShouldDetectFriendlies;
	AIPerceptionComponent->ConfigureSense(*SightConfig);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	BehaviorTreeComponent->StartLogic();
}

FGenericTeamId AEnemyController::GetGenericTeamId() const
{
	return AITeamID;
}

ETeamAttitude::Type AEnemyController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other))
	{
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
		}
	}
	return ETeamAttitude::Neutral;
}

void AEnemyController::ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	if (AGASMainCharacter* PlayerCharacter = Cast<AGASMainCharacter>(UpdatedActors[0]))
	{
		BlackboardComponent->SetValueAsObject("Player", UpdatedActors[0]);	
	}
}
