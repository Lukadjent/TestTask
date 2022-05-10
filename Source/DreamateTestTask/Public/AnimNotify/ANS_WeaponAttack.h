// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GAS/Character/AI/GASBaseCharacter.h"
#include "Inventory/Weapon/Weapon.h"
#include "ANS_WeaponAttack.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API UANS_WeaponAttack : public UAnimNotifyState
{
	GENERATED_BODY()

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY()
	AWeapon* Weapon; 
};
