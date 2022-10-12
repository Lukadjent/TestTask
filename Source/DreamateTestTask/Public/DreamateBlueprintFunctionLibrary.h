// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "DreamateBlueprintFunctionLibrary.generated.h"

class AAIController;

UCLASS()
class DREAMATETESTTASK_API UDreamateBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "DreamateBPFLibrary")
	static ETeamAttitude::Type GetAttitudeBetween(const AActor* A1, const AActor* A2);

	UFUNCTION(BlueprintCallable, Category = "DreamateBPFLibrary")
	static APlayerController* GetPlayerController(AActor* ControlledActor);

	UFUNCTION(BlueprintCallable, Category = "DreamateBPFLibrary")
	static AAIController* GetAIController(AActor* ControlledActor);
};
