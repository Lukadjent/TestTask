// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "NativeGameplayTags.h"

#include "Chaos/CollisionResolution.h"
#include "MaterialEditor/Public/MaterialStatsCommon.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = StaticMeshComponent;
	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxCollisionComponent->SetRelativeTransform(BoxCollisionTransform);
	BoxCollisionComponent->SetupAttachment(StaticMeshComponent);
	BoxCollisionComponent->SetGenerateOverlapEvents(false);
	BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	OwningPawn = Cast<AGASBaseCharacter>(GetParentActor());
	
}

void AWeapon::ClearAttackCounter()
{
	AttackCounter = 0;
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::OnAttack()
{
	GetWorldTimerManager().ClearTimer(ClearAttackCounterTimerHandle);
	AttackCounter = (AttackCounter + 1) % Montages.Num();
	GetWorldTimerManager().SetTimer(ClearAttackCounterTimerHandle, this, &AWeapon::ClearAttackCounter, 1.f, false, ComboTime);
}

void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{;
	SendAttackEvent(OtherActor);
}

void AWeapon::SendAttackEvent(AActor* Target)
{
	Target = Cast<AGASBaseCharacter>(Target);
	if (Target && Target != OwningPawn)
	{
		FGameplayTag Hit = FGameplayTag::RequestGameplayTag(HitTag);
		FGameplayEventData Data;
		Data.Instigator = OwningPawn;
		Data.Target = Target;
		Data.TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(Target);
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwningPawn, Hit, Data);	
	}
}

