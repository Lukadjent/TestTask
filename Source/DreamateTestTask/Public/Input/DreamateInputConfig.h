// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DreamateInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FDraemateInputAction
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

UCLASS()
class DREAMATETESTTASK_API UDreamateInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	UDreamateInputConfig();

	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

	TArray<FDraemateInputAction> GetNativeInputActions() const	{ return NativeInputActions; }

	TArray<FDraemateInputAction> GetAbilityInputActions() const { return AbilityInputActions; }

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"), meta = ( AllowPrivateAccess = "true"))
	TArray<FDraemateInputAction> NativeInputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"), meta = ( AllowPrivateAccess = "true"))
	TArray<FDraemateInputAction> AbilityInputActions;
};
