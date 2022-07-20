// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Weapon/Weapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "DreamateTestTask/Public/GAS/Character/AI/GASAIController.h"
#include "NativeGameplayTags.h"
#include "Chaos/CollisionResolution.h"
#include "Kismet/GameplayStatics.h"
#include "MaterialEditor/Public/MaterialStatsCommon.h"

// Create components
AWeapon::AWeapon()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = StaticMeshComponent;
	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxCollisionComponent->SetupAttachment(StaticMeshComponent);
	BoxCollisionComponent->SetGenerateOverlapEvents(false);
	BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnOverlapBegin);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	OwningPawn = Cast<AGASBaseCharacter>(GetParentActor());
	
}

void AWeapon::ClearAttackCounter()
{
	AttackCounter = 0;
}

void AWeapon::OnAttack()
{
	GetWorldTimerManager().ClearTimer(ClearAttackCounterTimerHandle);
	AttackCounter = (AttackCounter + 1) % AttacksInCombo;
	GetWorldTimerManager().SetTimer(ClearAttackCounterTimerHandle, this, &AWeapon::ClearAttackCounter, 1.f, false, ComboTime);
}

void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != OwningPawn)
	{
		if (!HitActors.Contains(OtherActor))
		{
			HitActors.Add(OtherActor);
			FGameplayEventData Data;
			Data.Instigator = OwningPawn;
			Data.Target = OtherActor;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwningPawn, Hit, Data);
		}
	}
}

UBoxComponent* AWeapon::GetBoxCollision() const
{
	return BoxCollisionComponent;
}

void AWeapon::SetHitTag(FGameplayTag HitTag)
{
	Hit = HitTag;
}

void AWeapon::ClearHitTargets()
{
	HitActors.Empty();
}

