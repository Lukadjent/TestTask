// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GASAIController.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API AGASAIController : public AAIController
{
	GENERATED_BODY()

	AGASAIController();

	virtual void BeginPlay() override;
	
protected:

#pragma region AI
	
	FGenericTeamId AITeamID;
	
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

	UPROPERTY()
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Perception")
	float SightRange = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Perception")
	float LoseSightRange = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Perception")
	float SightAngle = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Perception")
	float MaxAge = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Perception")
	bool bShouldDetectFriendlies = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Perception")
	bool bShouldDetectNeutrals = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Perception")
	bool bShouldDetectEnemies = true;
	
#pragma endregion

public:
	
	UFUNCTION(BlueprintCallable)
	ETeamAttitude::Type GetAttitudeTowards(const AActor* Other) const;

	virtual FGenericTeamId GetGenericTeamId() const override;

	UBlackboardComponent* GetBlackBoardComponent() const;

	UBehaviorTreeComponent* GetBehaviorTreeComponent() const;
};
