// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Death.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UDeath : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DREAMATETESTTASK_API IDeath
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	DECLARE_MULTICAST_DELEGATE(FCharacterDeath);
	FCharacterDeath CharacterDeath;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void NotifyDeath() const;
};
