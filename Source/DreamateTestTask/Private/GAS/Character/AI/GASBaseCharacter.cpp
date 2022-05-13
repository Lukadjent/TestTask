// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Character/AI/GASBaseCharacter.h"
#include "Inventory/InventoryComponent.h"
#include "DreamateTestTask/Public/Inventory/Weapon/Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"

// Create all components
AGASBaseCharacter::AGASBaseCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("AttributeSet"));
	StimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(
		TEXT("PerceptionStimuliSourceComponent"));
	WeaponComponent = CreateDefaultSubobject<UChildActorComponent>("WeaponComponent");
	WeaponComponent->SetupAttachment(GetMesh(), "Weapon_r");
	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
}

UAbilitySystemComponent* AGASBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UChildActorComponent* AGASBaseCharacter::GetWeaponComponent() const
{
	return WeaponComponent;
}

// Called when the game starts or when spawned
void AGASBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Giving default abilities
	for (const TTuple<EAbilities, TSubclassOf<UGameplayAbility>>& Ability : StandardAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability.Value, 1,static_cast<int32>(Ability.Key)));
	}

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

bool AGASBaseCharacter::ActivateAbilitiesWithItemSlot(FItemSlot ItemSlot)
{
	const FGameplayAbilitySpecHandle* SpecHandle = SlottedAbilities.Find(ItemSlot);
	if (SpecHandle && AbilitySystemComponent)
	{
		return AbilitySystemComponent->TryActivateAbility(*SpecHandle);
	}
	return false;
}

void AGASBaseCharacter::RemoveSlottedGameplayAbilities(FItemSlot InSlot)
{
	if (const FGameplayAbilitySpecHandle* SpecHandle  = SlottedAbilities.Find(InSlot))
	{
		AbilitySystemComponent->ClearAbility(*SpecHandle);
	}
	SlottedAbilities.Emplace(InSlot, FGameplayAbilitySpecHandle());
}

void AGASBaseCharacter::AddSlottedGameplayAbilities()
{
	TMap<FItemSlot, FGameplayAbilitySpec> SlottedAbilitySpecs;
	FillSlottedAbilitySpecs(SlottedAbilitySpecs);
	for (const TPair<FItemSlot, FGameplayAbilitySpec>& SpecPair : SlottedAbilitySpecs)
	{
		FGameplayAbilitySpecHandle& SpecHandle = SlottedAbilities.FindOrAdd(SpecPair.Key);
		if (!SpecHandle.IsValid())
		{
			SpecHandle = AbilitySystemComponent->GiveAbility(SpecPair.Value);
		}
	}
}

void AGASBaseCharacter::FillSlottedAbilitySpecs(TMap<FItemSlot, FGameplayAbilitySpec>& SlottedAbilitySpecs)
{
	if (Inventory)
	{
		const TMap<FItemSlot, UItemData*>& SlottedItemMap = Inventory->GetSlottedItemMap();
		for (const TPair<FItemSlot, UItemData*>& ItemPair : SlottedItemMap) 
		{
			const UItemData* SlottedItem = ItemPair.Value;
			if (SlottedItem && SlottedItem->GrantedAbility)
			{
				SlottedAbilitySpecs.Add(ItemPair.Key,FGameplayAbilitySpec(SlottedItem->GrantedAbility));
			}
		}
	}
}

bool AGASBaseCharacter::Attack()
{
	return ActivateAbilitiesWithItemSlot(Inventory->EquippedWeapon);
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