// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributesWidgetInterface.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "FloatingBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class DREAMATETESTTASK_API UFloatingBarWidget : public UUserWidget, public IAttributesWidgetInterface
{
	GENERATED_BODY()
	
	TSoftObjectPtr<AActor> OwningActor;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Settings", Meta = (AllowPrivateAccess))
	FGameplayAttribute Attribute;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Settings", Meta = (AllowPrivateAccess))
	FGameplayAttribute MaxAttribute;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Settings", Meta = (AllowPrivateAccess))
	FLinearColor BarColor;

public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Update();
	
	void SetColor(const FLinearColor& Color);
	
	void BindAttribute(const FGameplayAttribute& AttributeValue);

	void BindMaxAttribute(const FGameplayAttribute& AttributeValue);

	UFUNCTION(BlueprintCallable)
	void SetOwningActor(const AActor* Owner);

	UFUNCTION(BlueprintCallable)
	AActor* GetOwningActor() const;
};
