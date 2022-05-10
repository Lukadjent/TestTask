// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GC_PlaySound.h"

#include "Kismet/GameplayStatics.h"

bool UGC_PlaySound::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	if (Sound)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), Sound, Parameters.Location);	
	}
	return Super::OnExecute_Implementation(MyTarget, Parameters);
}
