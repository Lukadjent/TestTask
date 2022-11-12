// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "CharacterWidgetComponent.generated.h"


class UFloatingBarWidget;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DREAMATETESTTASK_API UCharacterWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
	UPROPERTY()
	UFloatingBarWidget* FloatingBarWidget;
	
public:
	// Sets default values for this component's properties
	UCharacterWidgetComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget | Settings")
	TSubclassOf<UFloatingBarWidget> FloatingBarClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget | Settings")
	FVector WidgetRelativeLocation = FVector(0.f,0.f, 120.f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget | Settings")
	FVector2D WidgetDrawSize = FVector2D(500.f, 500.f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget | Settings")
	EWidgetSpace WidgetSpace = EWidgetSpace::Screen;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget | Bar")
	FGameplayAttribute Attribute;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget | Bar")
	FGameplayAttribute MaxAttribute;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget | Bar")
	FLinearColor BarColor;
};
