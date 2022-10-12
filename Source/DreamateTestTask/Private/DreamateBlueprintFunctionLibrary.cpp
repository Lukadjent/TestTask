// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamateBlueprintFunctionLibrary.h"
#include "AIController.h"

ETeamAttitude::Type UDreamateBlueprintFunctionLibrary::GetAttitudeBetween(const AActor* A1, const AActor* A2)
{
	if (A1 && A2)
	{
		if (const APawn* P1 = Cast<APawn>(A1))
		{
			if (const IGenericTeamAgentInterface* Interface = Cast<IGenericTeamAgentInterface>(P1->GetController()))
			{
				return Interface->GetTeamAttitudeTowards(*A2);
			}
		}
	}
	return ETeamAttitude::Neutral;
}

APlayerController* UDreamateBlueprintFunctionLibrary::GetPlayerController(AActor* ControlledActor)
{
	const APawn* Pawn = Cast<APawn>(ControlledActor);
	if (Pawn)
	{
		return Cast<APlayerController>(Pawn->GetController());
	}
	return Cast<APlayerController>(ControlledActor);
}

AAIController* UDreamateBlueprintFunctionLibrary::GetAIController(AActor* ControlledActor)
{
	APawn* Pawn = Cast<APawn>(ControlledActor);
	if (Pawn)
	{
		return Cast<AAIController>(Pawn->GetController());
	}
	return Cast<AAIController>(ControlledActor);
}
