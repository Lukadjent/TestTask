// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/Obelisk.h"

#include "GAS/DreamateTestTaskGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AObelisk::OnInteraction(AGASBaseCharacter* Character)
{
	if (ADreamateTestTaskGameModeBase* Gamemode = Cast<ADreamateTestTaskGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		Gamemode->Victory();	
	}
}

