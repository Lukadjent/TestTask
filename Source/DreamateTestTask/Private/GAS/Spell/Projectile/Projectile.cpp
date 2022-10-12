// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Spell/Projectile/Projectile.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("StaticMesh");
	RootComponent = Collision;
	ParticleSystemComponent->SetupAttachment(Collision);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->SetUpdatedComponent(Collision);
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMovementComponent->InitialSpeed = Speed;
	ProjectileMovementComponent->MaxSpeed = Speed;
	if (GetInstigator())
	{
		ProjectileMovementComponent->Velocity = GetInstigator()->GetActorForwardVector() * ProjectileMovementComponent->InitialSpeed;
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

