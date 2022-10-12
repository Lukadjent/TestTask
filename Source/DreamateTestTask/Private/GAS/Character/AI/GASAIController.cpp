// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Character/AI/GASAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GAS/Character/Player/GASMainCharacter.h"
#include "Perception/AIPerceptionComponent.h"

AGASAIController::AGASAIController()
{
	AAIController::SetGenericTeamId(FGenericTeamId(1));
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = SightRange;
	SightConfig->LoseSightRadius = LoseSightRange;
	SightConfig->PeripheralVisionAngleDegrees = SightAngle;
	SightConfig->SetMaxAge(MaxAge);
	SightConfig->DetectionByAffiliation.bDetectEnemies = bShouldDetectEnemies;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = bShouldDetectNeutrals;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = bShouldDetectFriendlies;
	AIPerceptionComponent->ConfigureSense(*SightConfig);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
}

void AGASAIController::BeginPlay()
{
	Super::BeginPlay();
	BehaviorTreeComponent->StartLogic();
}

FGenericTeamId AGASAIController::GetGenericTeamId() const
{
	return AITeamID;
}

UBlackboardComponent* AGASAIController::GetBlackBoardComponent() const
{
	return BlackboardComponent;
}

UBehaviorTreeComponent* AGASAIController::GetBehaviorTreeComponent() const
{
	return BehaviorTreeComponent;
}

ETeamAttitude::Type AGASAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other))
	{
		if (OtherPawn->GetController()->Implements<UGenericTeamAgentInterface>())
		{
			return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
		}
	}
	return ETeamAttitude::Neutral;
}

void AGASAIController::ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	if (UpdatedActors[0]->IsA(AGASMainCharacter::StaticClass()))
	{
		BlackboardComponent->SetValueAsObject("Player", UpdatedActors[0]);
	}
}
