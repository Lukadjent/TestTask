// Fill out your copyright notice in the Description page of Project Settings.


#include "GASBaseEnemy.h"

#include "UnrealWidgetFwd.h"

AGASBaseEnemy::AGASBaseEnemy()
{
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetRelativeLocation(FVector(0.f,0.f, 120.f));
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawSize(FVector2d(500, 500));
	
}

void AGASBaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &AGASBaseEnemy::HealthChanged);
	
	InitializeDefaultAttributesAndEffects();

	FloatingBarWidget = CreateWidget<UFloatingBarWidget>(GetWorld(), FloatingBarClass);
	
	if (FloatingBarWidget && WidgetComponent)
	{
		WidgetComponent->SetWidget(FloatingBarWidget);

		if (AttributeSet)
		{
			FloatingBarWidget->SetCurrentHealth(AttributeSet->GetHealth());
			FloatingBarWidget->SetMaxHealth(AttributeSet->GetMaxHealth());
		}
	}
	
}

void AGASBaseEnemy::HealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;
	if (FloatingBarWidget)
	{
		FloatingBarWidget->SetCurrentHealth(Health);
	}
}
