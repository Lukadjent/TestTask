// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Spell/Projectile/Fireball/Fireball.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/Character/AI/GASBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void AFireball::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AFireball::OnOverlapBegin);
	SpawnLocation = GetActorLocation();
	Destination = FVector(Destination.X, Destination.Y, SpawnLocation.Z);
	const float TimelinePlayRate = Velocity / FVector::Distance(SpawnLocation, Destination);

	if (TimelineCurve)
	{
		FOnTimelineFloat OnTimelineUpdate;
		FOnTimelineEvent Finished;
		OnTimelineUpdate.BindUFunction(this, FName("Update"));
		Finished.BindUFunction(this, FName("Finished"));
		FloatCurveTimeline.AddInterpFloat(TimelineCurve, OnTimelineUpdate);
		FloatCurveTimeline.SetTimelineFinishedFunc(Finished);
		FloatCurveTimeline.SetPlayRate(TimelinePlayRate);
		FloatCurveTimeline.PlayFromStart();
	}
}

void AFireball::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FloatCurveTimeline.TickTimeline(DeltaSeconds);
}

void AFireball::Update(float Alpha)
{
	const FVector NewLocation = FMath::Lerp(SpawnLocation, Destination, Alpha);
	SetActorLocation(NewLocation, true);
}

void AFireball::Finished()
{
	Destroy();	
}

void AFireball::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Check If Fireball Collided With Something
	if (OtherComp->GetCollisionObjectType() == ECC_Pawn || OtherComp->GetCollisionObjectType() == ECC_WorldDynamic ||
		OtherComp->GetCollisionObjectType() == ECC_WorldStatic)
	{
		//Spawn Particles And Play Sound
		if (Explosion)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, FTransform(GetActorLocation()));
		}
		if (ExplosionSound)
		{
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
		}
		
		//Finding Actors In Explosion Area.
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
		ObjectType.Init(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn), 1);
		UClass* SearchForClass = AGASBaseCharacter::StaticClass();
		TArray<AActor*> IgnoreActors;
		IgnoreActors.Init(this, 1);
		TArray<AActor*> OutPutArray;
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), ExplosionRadius, ObjectType, SearchForClass ,IgnoreActors, OutPutArray);

		for (AActor* OverlappedActor : OutPutArray)
		{
			if (AGASBaseCharacter* Character = Cast<AGASBaseCharacter>(OverlappedActor))
			{
				const FGameplayEffectContextHandle Context = Character->GetAbilitySystemComponent()->MakeEffectContext();
				const FGameplayEffectSpecHandle SpecHandle = Character->GetAbilitySystemComponent()->MakeOutgoingSpec(DamageEffect, 1.f, Context);
				Character->GetAbilitySystemComponent()->BP_ApplyGameplayEffectSpecToSelf(UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageTag, Damage));
				FGameplayEventData Data;
				Data.Instigator = this;
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Character, Hit, Data);
			}
		}
		Destroy();
	}
}