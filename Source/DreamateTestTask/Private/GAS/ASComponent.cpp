// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ASComponent.h"

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

	for (const TTuple<EAbilities, TSubclassOf<UGameplayAbility>>& Ability : DefaultAbilities)
	{
		GiveAbility(FGameplayAbilitySpec(Ability.Value, 1,static_cast<int32>(Ability.Key)));
	}
	
}

bool UASComponent::Roll()
{
	if (!DefaultAbilities[EAbilities::Roll])
	{
		UE_LOG(LogTemp, Warning, TEXT("UASComponent: Roll Ability Isn't Given"));
		return false;
	}
	return TryActivateAbilityByClass(DefaultAbilities[EAbilities::Roll]);
}

bool UASComponent::Parry()
{
	if (!DefaultAbilities[EAbilities::Parry])
	{
		UE_LOG(LogTemp, Warning, TEXT("UASComponent: Parry Ability Isn't Given"));
		return false;
	}
	return TryActivateAbilityByClass(DefaultAbilities[EAbilities::Parry]);
}

bool UASComponent::CastSpell()
{
	if (!DefaultAbilities[EAbilities::CastSpell])
	{
		UE_LOG(LogTemp, Warning, TEXT("UASComponent: CastSpell Ability Isn't Given"));
		return false;
	}
	return TryActivateAbilityByClass(DefaultAbilities[EAbilities::CastSpell]);
}

bool UASComponent::UseConsumable()
{
	return ActivateAbilitiesWithItemSlot(UItemAssetManager::PotionItemType);
}

bool UASComponent::Attack()
{
	return ActivateAbilitiesWithItemSlot(UItemAssetManager::WeaponItemType);
}

bool UASComponent::ActivateAbilitiesWithItemSlot(FItemSlot ItemSlot)
{
	const FGameplayAbilitySpecHandle* SpecHandle = SlottedAbilities.Find(ItemSlot);
	if (SpecHandle)
	{
		return TryActivateAbility(*SpecHandle);
	}
	return false;
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
