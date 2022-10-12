// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "Components/BoxComponent.h"
#include "Obelisk.generated.h"

UCLASS()
class DREAMATETESTTASK_API AObelisk : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

	AObelisk();
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "StaticMeshComponent", meta = (AllowPrivateAccess))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BoxComponent", meta = (AllowPrivateAccess))
	UBoxComponent* BoxComponent;
	
public:

	//virtual void OnInteraction(AGASBaseCharacter* Character) override;
	virtual UObject* OnInteraction() override;
	
};
