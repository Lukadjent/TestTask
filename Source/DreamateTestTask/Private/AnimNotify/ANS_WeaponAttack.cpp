// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/ANS_WeaponAttack.h"

#include "Inventory/Weapon/Weapon.h"

void UANS_WeaponAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (AGASBaseCharacter* Character = Cast<AGASBaseCharacter>(MeshComp->GetOwner()))
	{
		Weapon = Cast<AWeapon>(Character->GetWeaponComponent()->GetChildActor());
		if (Weapon)
		{
			Weapon->SetHitTag(WeaponHitTag);
			Weapon->GetBoxCollision()->SetGenerateOverlapEvents(true);
		}
	}
}

void UANS_WeaponAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (Weapon)
	{
		Weapon->ClearHitTargets();
		Weapon->GetBoxCollision()->SetGenerateOverlapEvents(false);
	}
}