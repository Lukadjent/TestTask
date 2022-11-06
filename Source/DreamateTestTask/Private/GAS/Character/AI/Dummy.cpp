// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Character/AI/Dummy.h"

ADummy::ADummy()
{
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetRelativeLocation(FVector(0.f,0.f, 120.f));
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawSize(FVector2d(500, 500));
}

void ADummy::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeDefaultAttributesAndEffects();
	
	FloatingBarWidget = CreateWidget<UFloatingBarWidget>(GetWorld(), FloatingBarClass);
	
	if (FloatingBarWidget && WidgetComponent)
	{
		FloatingBarWidget->UpdateColor(FLinearColor(1.f, 0.f,0.f,1.f));
		
		if (AttributeSet)
		{
			AbilitySystemComponent->BindAttributeToWidget(AttributeSet->GetHealthAttribute(),
			                                              AttributeSet->GetMaxHealthAttribute(), FloatingBarWidget.Get());
		}

		WidgetComponent->SetWidget(FloatingBarWidget);
	}
}

void ADummy::ImmobileTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	
}

