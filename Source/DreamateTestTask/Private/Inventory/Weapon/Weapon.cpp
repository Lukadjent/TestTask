// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Weapon/Weapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "DreamateTestTask/Public/GAS/Character/AI/GASAIController.h"
#include "NativeGameplayTags.h"
#include "Chaos/CollisionResolution.h"
#include "Kismet/GameplayStatics.h"

// Create components
AWeapon::AWeapon()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxCollisionComponent->SetupAttachment(StaticMeshComponent);
	BoxCollisionComponent->SetGenerateOverlapEvents(false);
	BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnOverlapBegin);
	BoxCollisionComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = GetParentActor();

	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("AWeapon: Failed To Initialize OWNER in AWeapon.cpp!"));
		return;
	}

}

void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != Owner)
	{
		if (!HitActors.Contains(OtherActor))
		{
			HitActors.Add(OtherActor);
			FGameplayEventData Data;
			Data.Instigator = Owner;
			Data.Target = OtherActor;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, Hit, Data);
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

