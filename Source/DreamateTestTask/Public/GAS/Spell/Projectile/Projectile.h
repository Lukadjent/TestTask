// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class DREAMATETESTTASK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<USphereComponent> Collision;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UParticleSystemComponent> ParticleSystemComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FGameplayTag DamageTag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FGameplayTag Hit;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UGameplayEffect> DamageEffect;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float SphereCollisionRadius;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn))
	float Damage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn))
	float Speed;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
