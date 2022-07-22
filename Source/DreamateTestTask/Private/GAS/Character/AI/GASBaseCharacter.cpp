// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Character/AI/GASBaseCharacter.h"
#include "Inventory/InventoryComponent.h"
#include "DreamateTestTask/Public/Inventory/Weapon/Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Inventory/Item/WeaponItemData.h"

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
}

UChildActorComponent* AGASBaseCharacter::GetWeaponComponent() const
{
	return WeaponComponent;
}

// Called when the game starts or when spawned
void AGASBaseCharacter::BeginPlay()
{
	Inventory->OnSlottedItemChangedNative.AddUObject(this, &AGASBaseCharacter::SlottedItemChanged);
	
	Super::BeginPlay();
	
	//Binding function on MoveSpeedChange
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMoveSpeedAttribute()).
	                             AddUObject(this, &AGASBaseCharacter::OnMovementSpeedChange);
	//Binding function on Immobile tag added/removed
	AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("Status.Immobile")),
	                                                 EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AGASBaseCharacter::ImmobileTagChanged);
	
}

void AGASBaseCharacter::InitializeDefaultAttributesAndEffects()
{
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	
	for (const TSubclassOf<UGameplayEffect>& Effect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 0.f, EffectContext);
		if (NewHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
		}
	}
}

UASComponent* AGASBaseCharacter::GetAbilitySystemComponent() const 
{
	return AbilitySystemComponent;
}

UInventoryComponent* AGASBaseCharacter::GetInventoryComponent() const
{
	return Inventory;
}

void AGASBaseCharacter::OnMovementSpeedChange(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->MaxWalkSpeed = AttributeSet->GetMoveSpeed();
}

void AGASBaseCharacter::ImmobileTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
}

void AGASBaseCharacter::NotifyDeath()
{
	CharacterDeath.Broadcast(this);
}

void AGASBaseCharacter::SlottedItemChanged(FItemSlot ItemSlot, UItemData* Item)
{
	if (ItemSlot.GetItemType() == UItemAssetManager::WeaponItemType)
	{
		if (const UWeaponItemData* WeaponData = Cast<UWeaponItemData>(Item))
		{
			WeaponComponent->SetChildActorClass(WeaponData->GetWeaponClass());
		}
	}
	AbilitySystemComponent->RemoveSlottedGameplayAbilities(ItemSlot);
	AbilitySystemComponent->AddSlottedGameplayAbilities();
}