// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttributeSet.h"

#include "GASBaseCharacter.h"

void UBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{

	Super::PreAttributeChange(Attribute, NewValue);
	
	// if (AGASBaseCharacter* Char = Cast<AGASBaseCharacter>(GetOwningActor()))
	// {
	// 	if (Attribute == GetHealthAttribute())
	// 	{
	// 		NewValue = FMath::Clamp<float>(NewValue, 0, GetMaxHealth());
	// 		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("%f"), NewValue));
	// 		FGameplayTag Tag;
	// 		if (NewValue <= 0)
	// 		{
	// 			Tag.FromExportString(DeathTag);
	// 		}
	// 		else
	// 		{
	// 			Tag.FromExportString(TakeDamageTag);
	// 		}
	// 		GetOwningAbilitySystemComponent()->AddLooseGameplayTag(Tag);
	// 	}	
	// }
}

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
