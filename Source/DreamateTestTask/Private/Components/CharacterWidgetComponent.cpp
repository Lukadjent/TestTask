// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterWidgetComponent.h"

#include "UI/FloatingBarWidget.h"


// Sets default values for this component's properties
UCharacterWidgetComponent::UCharacterWidgetComponent()
{
	SetRelativeLocation(WidgetRelativeLocation);
	SetWidgetSpace(WidgetSpace);
	SetDrawSize(DrawSize);
}


// Called when the game starts
void UCharacterWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	FloatingBarWidget = CreateWidget<UFloatingBarWidget>(GetWorld(), FloatingBarClass);

	if (FloatingBarWidget)
	{
		FloatingBarWidget->SetColor(BarColor);
		FloatingBarWidget->BindAttribute(Attribute);
		FloatingBarWidget->BindMaxAttribute(MaxAttribute);
		FloatingBarWidget->SetOwningActor(GetOwner());
		FloatingBarWidget->Update();
		SetWidget(FloatingBarWidget);
	}
	
}



