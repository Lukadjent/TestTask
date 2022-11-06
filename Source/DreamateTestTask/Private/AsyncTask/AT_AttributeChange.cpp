// Fill out your copyright notice in the Description page of Project Settings.

#include "DreamateTestTask/Public/AsyncTask/AT_AttributeChange.h"

UAT_AttributeChange* UAT_AttributeChange::ListenForAttributeChange(
	UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
	UAT_AttributeChange* WaitForAttributeChangeTask = NewObject<UAT_AttributeChange>();
	WaitForAttributeChangeTask->ASC = AbilitySystemComponent;
	WaitForAttributeChangeTask->AttributeToListenFor = Attribute;

	if (!IsValid(AbilitySystemComponent) || !Attribute.IsValid())
	{
		WaitForAttributeChangeTask->RemoveFromRoot();
		return nullptr;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(
		WaitForAttributeChangeTask, &UAT_AttributeChange::AttributeChanged);

	return WaitForAttributeChangeTask;
}

UAT_AttributeChange* UAT_AttributeChange::ListenForAttributesChange(
	UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAttribute> Attributes)
{
	UAT_AttributeChange* WaitForAttributeChangeTask = NewObject<UAT_AttributeChange>();
	WaitForAttributeChangeTask->ASC = AbilitySystemComponent;
	WaitForAttributeChangeTask->AttributesToListenFor = Attributes;

	if (!IsValid(AbilitySystemComponent) || Attributes.Num() < 1)
	{
		WaitForAttributeChangeTask->RemoveFromRoot();
		return nullptr;
	}

	for (const auto& Attribute : Attributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(
			WaitForAttributeChangeTask, &UAT_AttributeChange::AttributeChanged);
	}
	
	return WaitForAttributeChangeTask;
}

void UAT_AttributeChange::EndTask()
{
	if (IsValid(ASC.Get()))
	{
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);
		for(const auto& Attribute : AttributesToListenFor)
		{
			ASC->GetGameplayAttributeValueChangeDelegate(Attribute).RemoveAll(this);	
		}
	}
	SetReadyToDestroy();
	MarkAsGarbage();
}

void UAT_AttributeChange::AttributeChanged(const FOnAttributeChangeData& Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}
