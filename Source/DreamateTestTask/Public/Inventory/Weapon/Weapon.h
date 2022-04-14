// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GAS/Character/AI/GASBaseCharacter.h"
#include "Weapon.generated.h"

UCLASS()
class DREAMATETESTTASK_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle ClearAttackCounterTimerHandle;

	void ClearAttackCounter();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* BoxCollisionComponent;

	UPROPERTY(EditDefaultsOnly)
	FTransform StaticMeshTransform;

	UPROPERTY(EditDefaultsOnly)
	FTransform BoxCollisionTransform;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	
	UPROPERTY(BlueprintReadOnly)
	int AttackCounter = 0;

	float ComboTime = 2.f;

	FName HitTag = "Weapon.Hit";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Damage;

	UFUNCTION(BlueprintCallable)
	void OnAttack();

	UPROPERTY()
	AGASBaseCharacter* OwningPawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<UAnimMontage*> Montages;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void SendAttackEvent(AActor* Target);
};
