// Fill out your copyright notice in the Description page of Project Settings.


#include "DreamateTestTask/Public/UI/FloatingBarWidget.h"


void UFloatingBarWidget::SetColor(const FLinearColor& Color)
{
	BarColor = Color;
}

void UFloatingBarWidget::BindAttribute(const FGameplayAttribute& AttributeValue)
{
	Attribute = AttributeValue;
}

void UFloatingBarWidget::BindMaxAttribute(const FGameplayAttribute& AttributeValue)
{
	MaxAttribute = AttributeValue;
}

void UFloatingBarWidget::SetOwningActor(const AActor* Owner)
{
	OwningActor = Owner;
}

AActor* UFloatingBarWidget::GetOwningActor() const
{
	return OwningActor.Get();
}
