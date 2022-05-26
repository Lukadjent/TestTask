// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "UObject/NoExportTypes.h"
#include "TargetType.generated.h"

class AGASBaseCharacter;

UCLASS(Blueprintable, meta = (ShowWorldContextPin))
class DREAMATETESTTASK_API UTargetType : public UObject
{
	GENERATED_BODY()

public:
	UTargetType() {}

	UFUNCTION(BlueprintNativeEvent)
	void GetTargets(AGASBaseCharacter* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const;
};

UCLASS(NotBlueprintable)
class DREAMATETESTTASK_API UTargetType_UseOwner : public UTargetType
{
	GENERATED_BODY()
public:
	UTargetType_UseOwner() {}

	virtual void GetTargets_Implementation(AGASBaseCharacter* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const override;
	
};

UCLASS(NotBlueprintable)
class DREAMATETESTTASK_API UTargetType_UseEventData : public UTargetType
{
	GENERATED_BODY()
public:
	UTargetType_UseEventData() {}

	virtual void GetTargets_Implementation(AGASBaseCharacter* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const override;
	
};

UCLASS(Blueprintable)
class DREAMATETESTTASK_API UTargetType_Sphere : public UTargetType
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Settings")
	FVector OffsetFromActor;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Settings")
	float SphereRadius;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Settings")
	float TraceLength;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Settings")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	
public:
	UTargetType_Sphere() {}

	virtual void GetTargets_Implementation(AGASBaseCharacter* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const override;
};