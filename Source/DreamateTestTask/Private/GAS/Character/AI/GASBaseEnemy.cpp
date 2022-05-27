// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Character/AI/GASBaseEnemy.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/FloatingBarWidget.h"

//Create widget component and set the variables of it
AGASBaseEnemy::AGASBaseEnemy()
{
	
	/*WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetRelativeLocation(FVector(0.f,0.f, 120.f));
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawSize(FVector2d(500, 500));*/
	
}

void AGASBaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	/*//Bind function on health attribute changed
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
	}*/
	
}

/*void AGASBaseEnemy::HealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;
	if (FloatingBarWidget)
	{
		FloatingBarWidget->SetCurrentHealth(Health);
	}
}*/

void AGASBaseEnemy::ImmobileTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_None);
		GetController()->StopMovement();
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
}

TArray<ATargetPoint*> AGASBaseEnemy::GetPatrolPoints() const
{
	return PatrolPoints;
}

void AGASBaseEnemy::SpawnLoot()
{
	if (!Drop.IsEmpty())
	{
		if (UKismetMathLibrary::RandomBoolWithWeight(DropProbability))
		{
			const TSubclassOf<APickUpBase> Class = Drop[FMath::RandRange(0, Drop.Num() - 1)];
			const FVector SpawnLocation = GetActorLocation() - FVector(0.f,0.f, 80.f);
			GetWorld()->SpawnActor(Class, &SpawnLocation);	
		}
	}
}
