// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ASComponent.h"
#include "GAS/Ability/AbilityBindingInterface.h"
#include "Inventory/InventoryComponent.h"
#include "Inventory/InventoryInterface.h"


// Sets default values for this component's properties
UASComponent::UASComponent()
{
	
}


// Called when the game starts
void UASComponent::BeginPlay()
{
	Super::BeginPlay();
	
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
					SlottedAbilitySpecs.Add(ItemPair.Key,FGameplayAbilitySpec(SlottedItem->GrantedAbility));
				}
			}
		}
	}
}

void UASComponent::BindAttributeToWidget(FGameplayAttribute Attribute, FGameplayAttribute AttributeMax, TScriptInterface<IAttributesWidgetInterface> Widget) const
{
	IAttributesWidgetInterface::Execute_SetAttribute(Widget.GetObject(), Attribute);
	IAttributesWidgetInterface::Execute_SetAttributeMax(Widget.GetObject(), AttributeMax);
	IAttributesWidgetInterface::Execute_SetAbilitySystemComponent(Widget.GetObject(), this);
}
