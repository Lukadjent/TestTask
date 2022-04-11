// Fill out your copyright notice in the Description page of Project Settings.


#include "GE_Damage.h"

UGE_Damage::UGE_Damage()
{
	FGameplayModifierInfo Info;
	Info.Attribute.AttributeName = "Damage";
	Info.ModifierOp = EGameplayModOp::Override;
	FGameplayTag Tag;
	Tag.FromExportString("Attribute.Damage");
//	Info.ModifierMagnitude.GetMagnitudeCalculationType()::SetByCaller;
	Modifiers.Add(Info);
}
