// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GAS/Spell/Projectile/Projectile.h"
#include "Fireball.generated.h"

class UCurveFloat;

UCLASS()
class DREAMATETESTTASK_API AFireball : public AProjectile
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

	
protected:

	UPROPERTY(EditAnywhere, Category = "Particle")
	UParticleSystem* Explosion;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TSoftObjectPtr<USoundBase> ExplosionSound;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn))
	float ExplosionRadius;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);

	void Explode();
};