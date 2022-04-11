// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Projectile.h"
#include "Fireball.generated.h"

/**
 * 
 */

class UCurveFloat;

UCLASS()
class DREAMATETESTTASK_API AFireball : public AProjectile
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION()
	void Update(float Alpha);

	UFUNCTION()
	void Finished();
	
protected:

	FTimeline FloatCurveTimeline;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* TimelineCurve;

	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, Category = "Particle")
	UParticleSystem* Explosion;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn))
	FVector Destination;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn))
	float ExplosionRadius;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
