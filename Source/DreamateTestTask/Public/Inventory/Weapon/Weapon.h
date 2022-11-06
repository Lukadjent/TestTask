// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GAS/Character/AI/GASBaseCharacter.h"
#include "Weapon.generated.h"

class UWeaponItemData;
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> BoxCollisionComponent;

#pragma region WEAPON_DATA
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon")
	TSoftObjectPtr<UWeaponItemData> ItemData;

	FGameplayTag Hit;

	UPROPERTY()
	TArray<AActor*> HitActors;
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#pragma endregion 

public:
	
	UBoxComponent* GetBoxCollision() const;

	void SetHitTag(FGameplayTag HitTag);

	void ClearHitTargets();
};
