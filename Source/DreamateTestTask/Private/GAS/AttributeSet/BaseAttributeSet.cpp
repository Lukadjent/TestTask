// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/AttributeSet/BaseAttributeSet.h"

#include "DreamateTestTask/Public/GAS/Character/AI/GASBaseCharacter.h"

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float DealtDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if (DealtDamage > 0.f)
		{
			const float NewHealth = GetHealth() - DealtDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));
			FGameplayTag Tag;
			//If new health > 0.f - Character took damage, otherwise he died.
			if (GetHealth() > 0.f)
			{
				Tag.FromExportString(TakeDamageTag);
			}
			else
			{
				Tag.FromExportString(DeathTag);
			}
			GetOwningAbilitySystemComponent()->AddLooseGameplayTag(Tag);
		}
	}
	
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		const float NewStamina = GetStamina();
		SetStamina(FMath::Clamp(NewStamina, 0.f, GetMaxStamina()));
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		const float NewHealth = GetHealth();
		SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		const float NewMana = GetMana();
		SetMana(FMath::Clamp(NewMana, 0.f, GetMaxMana()));
	}
}
