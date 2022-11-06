// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Spell/Projectile/Fireball/Fireball.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/AbilitySystemComponentInterface.h"
#include "GAS/ASComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void AFireball::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentHit.AddDynamic(this, &AFireball::OnHit);
}

void AFireball::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	//Spawn Particles And Play Sound
	if (Explosion)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, FTransform(GetActorLocation()));
	}
	if (ExplosionSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ExplosionSound.Get(), GetActorLocation());
	}
	Explode();
}

void AFireball::Explode()
{
//Finding Actors In Explosion Area.
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	ObjectType.Init(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn), 1);
	UClass* SearchForClass = nullptr;
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Init(this, 1);
	TArray<AActor*> OutPutArray;
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), ExplosionRadius, ObjectType, SearchForClass ,IgnoreActors, OutPutArray);
	for (AActor* OverlappedActor : OutPutArray)
	{
		if (const IAbilitySystemComponentInterface* ASC = Cast<IAbilitySystemComponentInterface>(OverlappedActor))
		{
			const FGameplayEffectContextHandle Context = ASC->GetAbilitySystemComponent()->MakeEffectContext();
			const FGameplayEffectSpecHandle SpecHandle = ASC->GetAbilitySystemComponent()->MakeOutgoingSpec(DamageEffect, 1.f, Context);
			ASC->GetAbilitySystemComponent()->BP_ApplyGameplayEffectSpecToSelf(UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageTag, Damage));
			FGameplayEventData Data;
			Data.Instigator = this;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OverlappedActor, Hit, Data);
		}
	}
	Destroy();
}
