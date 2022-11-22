// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Character/AI/GASBaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Inventory/InventoryComponent.h"
#include "DreamateTestTask/Public/Inventory/Weapon/Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/Ability/AbilitySet.h"

// Create all components
AGASBaseCharacter::AGASBaseCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UASComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("AttributeSet"));
	StimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(
		TEXT("PerceptionStimuliSourceComponent"));
	WeaponComponent = CreateDefaultSubobject<UChildActorComponent>("WeaponComponent");
	WeaponComponent->SetupAttachment(GetMesh(), "Weapon_r");
	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
}

// Called when the game starts or when spawned
void AGASBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitializeDefaultAttributesAndEffects();
}

void AGASBaseCharacter::NotifyDeath_Implementation() const
{
	CharacterDeath.Broadcast();
}

#pragma region GETTERS

UChildActorComponent* AGASBaseCharacter::GetWeaponComponent() const
{
	return WeaponComponent;
}

UBaseAttributeSet* AGASBaseCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

UCharacterMovementComponent* AGASBaseCharacter::GetCharacterMovementComponent() const
{
	return GetCharacterMovement();
}

UASComponent* AGASBaseCharacter::GetAbilitySystemComponent() const 
{
	return AbilitySystemComponent;
}

UInventoryComponent* AGASBaseCharacter::GetInventoryComponent() const
{
	return Inventory;
}

#pragma endregion 