// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ASComponent.h"
#include "GAS/Ability/AbilityBindingInterface.h"
#include "Inventory/InventoryComponent.h"
#include "Inventory/InventoryInterface.h"
#include "Inventory/Item/WeaponItemData.h"


// Sets default values for this component's properties
UASComponent::UASComponent()
{
	
}


// Called when the game starts
void UASComponent::BeginPlay()
{
	Super::BeginPlay();

	IInventoryInterface* Inventory = Cast<IInventoryInterface>(GetOwner());
	if (Inventory)
	{
		Inventory->GetInventoryComponent()->OnSlottedItemChangedNative.AddUObject(this, &UASComponent::SlottedItemChanged);
	}
	
}

void UASComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	const IAbilityBindingInterface* ABI = Cast<IAbilityBindingInterface>(GetAvatarActor_Direct());
	if (ABI)
	{
		ABI->BindAbility(AbilitySpec);
	}
	
	Super::OnGiveAbility(AbilitySpec);
}

void UASComponent::OnRemoveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	const IAbilityBindingInterface* ABI = Cast<IAbilityBindingInterface>(GetAvatarActor_Direct());
	if (ABI)
	{
		ABI->UnbindAbility(AbilitySpec);
	}
	
	Super::OnRemoveAbility(AbilitySpec);
}

void UASComponent::SlottedItemChanged(FItemSlot ItemSlot, UItemData* Item)
{
	const IInventoryInterface* Inventory = Cast<IInventoryInterface>(GetOwner());
	if (Inventory)
	{
		if (ItemSlot.GetItemType() == UItemAssetManager::WeaponItemType)
		{
			if (const UWeaponItemData* WeaponData = Cast<UWeaponItemData>(Item))
			{
				Inventory->GetWeaponComponent()->SetChildActorClass(WeaponData->GetWeaponClass());
			}
		}
		RemoveSlottedGameplayAbilities(ItemSlot);
		AddSlottedGameplayAbilities();
	}
}

void UASComponent::RemoveSlottedGameplayAbilities(FItemSlot InSlot)
{
	if (const FGameplayAbilitySpecHandle* SpecHandle  = SlottedAbilities.Find(InSlot))
	{
		ClearAbility(*SpecHandle);
	}
	SlottedAbilities.Emplace(InSlot, FGameplayAbilitySpecHandle());
}

void UASComponent::AddSlottedGameplayAbilities()
{
	TMap<FItemSlot, FGameplayAbilitySpec> SlottedAbilitySpecs;
	FillSlottedAbilitySpecs(SlottedAbilitySpecs);
	for (const TPair<FItemSlot, FGameplayAbilitySpec>& SpecPair : SlottedAbilitySpecs)
	{
		FGameplayAbilitySpecHandle& SpecHandle = SlottedAbilities.FindOrAdd(SpecPair.Key);
		if (!SpecHandle.IsValid())
		{
			SpecHandle = GiveAbility(SpecPair.Value);
		}
	}
}

void UASComponent::FillSlottedAbilitySpecs(TMap<FItemSlot, FGameplayAbilitySpec>& SlottedAbilitySpecs)
{
	const IInventoryInterface* InventoryInterface = Cast<IInventoryInterface>(GetOwner());
	if (InventoryInterface)
	{
		const UInventoryComponent* Inventory = InventoryInterface->GetInventoryComponent();
		if (Inventory)
		{
			const TMap<FItemSlot, UItemData*>& SlottedItemMap = Inventory->GetSlottedItemMap();
			for (const TPair<FItemSlot, UItemData*>& ItemPair : SlottedItemMap) 
			{
				const UItemData* SlottedItem = ItemPair.Value;
				if (SlottedItem && SlottedItem->GrantedAbility)
				{
					SlottedAbilitySpecs.Add(ItemPair.Key,FGameplayAbilitySpec(SlottedItem->GrantedAbility, 0, 0));
				}
			}
		}
	}
}

void UASComponent::InitializeDefaultAttributesAndEffects()
{
	FGameplayEffectContextHandle EffectContext = MakeEffectContext();
	EffectContext.AddSourceObject(this);
	
	for (const TSubclassOf<UGameplayEffect>& Effect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = MakeOutgoingSpec(Effect, 0.f, EffectContext);
		if (NewHandle.IsValid())
		{
			ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
		}
	}
}
