// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

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
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

