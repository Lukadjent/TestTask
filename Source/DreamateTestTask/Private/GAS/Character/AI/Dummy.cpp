// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Character/AI/Dummy.h"

ADummy::ADummy()
{
	WidgetComponent = CreateDefaultSubobject<UCharacterWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);
}

void ADummy::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeDefaultAttributesAndEffects();
	
}

void ADummy::ImmobileTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	
}

