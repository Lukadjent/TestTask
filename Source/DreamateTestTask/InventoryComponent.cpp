// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;
	
	
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AGASBaseCharacter>(GetOwner());
	
	Initialize();
	
}


void UInventoryComponent::AddDefaults()
{
	for (auto& Item : DefaultSlots)
	{
		//AddItem(Item, DefaultSlots[Item]);
	}
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UInventoryComponent::EquipWeapon(TSubclassOf<AWeapon> Weapon)
{
	EquippedWeapon = Weapon;
	Owner->WeaponComponent->SetChildActorClass(EquippedWeapon);
	
}

void UInventoryComponent::EquipConsumable(TSubclassOf<AConsumable> Consumable)
{
	EquippedConsumable = Consumable;
}

void UInventoryComponent::Unequip(TSubclassOf<AItem> Item)
{
	
	//Owner->GetAbilitySystemComponent()->RemoveLooseGameplayTag();
}

void UInventoryComponent::Initialize()
{
	//AddDefaults();
	EquipWeapon(DefaultEquippedWeapon);
	EquipConsumable(DefaultEquippedConsumable);
}

void UInventoryComponent::AddItem(TSubclassOf<AItem> Item, int Quantity)
{
	Inventory.Emplace(Item, Inventory[Item] + Quantity);
}

void UInventoryComponent::SwitchWeapon(const EWeaponType NewWeapon) const
{
	if (Owner->Weapon != NewWeapon)
	{
		//RemoveAbility;
		Owner->Weapon = NewWeapon;
		//GiveNewOne;	
	}
}

