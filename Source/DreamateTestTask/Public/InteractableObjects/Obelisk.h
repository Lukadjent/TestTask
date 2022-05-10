// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "Obelisk.generated.h"

UCLASS()
class DREAMATETESTTASK_API AObelisk : public AInteractableBase
{
	GENERATED_BODY()

public:

	virtual void OnInteraction(AGASBaseCharacter* Character) override;
};
