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

	FTimerHandle ClearAttackCounterTimerHandle;

	void ClearAttackCounter();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* BoxCollisionComponent;

	UPROPERTY(EditDefaultsOnly)
	FTransform BoxCollisionTransform;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon")
	UWeaponItemData* ItemData;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon")
	FItemSlot Slot;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Sound")
	USoundBase* HitSound;
	
	UPROPERTY(BlueprintReadOnly)
	int AttackCounter = 0;

	FName HitTag = "Weapon.Hit";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Damage;

	UFUNCTION(BlueprintCallable)
	void OnAttack();

	UPROPERTY()
	AGASBaseCharacter* OwningPawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Moveset")
	UAnimMontage* Montage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Moveset")
	int32 AttacksInCombo = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Moveset")
	float ComboTime = 2.f;
	
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void SendAttackEvent(AActor* Target);

public:
	UBoxComponent* GetBoxCollision() const;

};
