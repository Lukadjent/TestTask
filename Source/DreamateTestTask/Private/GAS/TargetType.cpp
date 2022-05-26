// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/TargetType.h"
#include "GAS/Character/AI/GASBaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"

void UTargetType::GetTargets_Implementation(AGASBaseCharacter* TargetingCharacter, AActor* TargetingActor,
                                            FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
}

void UTargetType_UseOwner::GetTargets_Implementation(AGASBaseCharacter* TargetingCharacter, AActor* TargetingActor,
	FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
	OutActors.Add(TargetingCharacter);
}

void UTargetType_UseEventData::GetTargets_Implementation(AGASBaseCharacter* TargetingCharacter, AActor* TargetingActor,
	FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
	const FHitResult* FoundHitResult = EventData.ContextHandle.GetHitResult();
	if (FoundHitResult)
	{
		OutHitResults.Add(*FoundHitResult);
	}
	else if (EventData.Target)
	{
		OutActors.Add(const_cast<AActor*>(EventData.Target));
	}
}

void UTargetType_Sphere::GetTargets_Implementation(AGASBaseCharacter* TargetingCharacter, AActor* TargetingActor,
	FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
	const FVector TraceStart = UKismetMathLibrary::TransformLocation(TargetingCharacter->GetTransform(), OffsetFromActor);
	const FVector TraceEnd = TargetingCharacter->GetActorForwardVector() * TraceLength + TargetingCharacter->GetActorLocation();
	const TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> TempHitResults;
	UKismetSystemLibrary::SphereTraceMultiForObjects(TargetingCharacter, TraceStart, TraceEnd, SphereRadius, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, TempHitResults, true);
	for (FHitResult HitResult : TempHitResults)
	{
		if (HitResult.GetActor())
		{
			OutActors.AddUnique(HitResult.GetActor());
		}
	}
}
