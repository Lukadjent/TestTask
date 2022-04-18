// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Character/AI/GASBaseCharacter.h"
#include "Inventory/InventoryComponent.h"
#include "DreamateTestTask/Public/Inventory/Weapon/Weapon.h"

// Sets default values
AGASBaseCharacter::AGASBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

// Called when the game starts or when spawned
void AGASBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	for (const auto& Ability : StandardAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability.Value, 1,static_cast<int32>(Ability.Key)));
	}
	
}

void AGASBaseCharacter::InitializeDefaultAttributesAndEffects()
{
	if (DefaultAttributes)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 0.f, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
		}
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	
	for (const auto& Effect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 0.f, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
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


// Called every frame
void AGASBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGASBaseCharacter::Attack()
{
	return ActivateAbilitiesWithItemSlot(Inventory->EquippedWeapon);
}