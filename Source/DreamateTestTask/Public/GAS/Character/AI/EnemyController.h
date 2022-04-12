// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API AEnemyController : public AAIController
{
	GENERATED_BODY()

	AEnemyController();

	virtual void BeginPlay() override;
	
public:

#pragma region AI
	
	FGenericTeamId AITeamID;

	virtual FGenericTeamId GetGenericTeamId() const override;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI | Behaviour")
	UBehaviorTreeComponent* BehaviorTreeComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI | Behaviour")
	UBlackboardComponent* BlackboardComponent;
	
#pragma endregion
	
#pragma region PERCEPTION

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI | Perception")
	UAIPerceptionComponent* AIPerceptionComponent;

	virtual void ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors) override;
	
protected:

	UPROPERTY()
	UAISenseConfig_Sight* SightConfig;
	float SightRange = 1000.f;
	float LoseSightRange = 1500.f;
	float SightAngle = 100.f;
	float MaxAge = 0.f;
	bool bShouldDetectFriendlies = true;
	
#pragma endregion
	
};
