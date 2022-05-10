// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "InteractableBase.generated.h"

class AGASBaseCharacter;

UCLASS()
class DREAMATETESTTASK_API AInteractableBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "StaticMeshComponent")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BoxComponent")
	UBoxComponent* BoxComponent;
	
public:

	virtual void OnInteraction(AGASBaseCharacter* Character);
};
