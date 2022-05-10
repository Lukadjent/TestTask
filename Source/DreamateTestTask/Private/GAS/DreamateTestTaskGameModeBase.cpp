// Copyright Epic Games, Inc. All Rights Reserved.


#include "DreamateTestTask/Public/GAS/DreamateTestTaskGameModeBase.h"

#include "Inventory/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

void ADreamateTestTaskGameModeBase::BeginPlay()
{
	//Super::BeginPlay();
	PlayerCharacter = Cast<AGASMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		PlayerCharacter->CharacterDeath.AddUObject(this, &ADreamateTestTaskGameModeBase::OnPlayerCharacterDeath);
	}
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGASBaseCharacter::StaticClass(), Actors);
	for (AActor* Actor : Actors)
	{
		if (AGASBaseEnemy* Enemy = Cast<AGASBaseEnemy>(Actor))
		{
			Enemies.Add(Enemy);
			Enemy->CharacterDeath.AddUObject(this, &ADreamateTestTaskGameModeBase::OnEnemyDeath);
		}
	}
}

void ADreamateTestTaskGameModeBase::OnEnemyDeath(AGASBaseCharacter* Enemy)
{
	Enemies.Remove(Enemy);
	if (AGASBaseEnemy* Test = Cast<AGASBaseEnemy>(Enemy))
	{
		Test->SpawnLoot();
	}
	if (Enemies.IsEmpty())
	{
		Victory();
	}
}

void ADreamateTestTaskGameModeBase::OnPlayerCharacterDeath(AGASBaseCharacter* Character)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Lose"));
	PlayAgainWidget = CreateWidget<UPlayAgainWidget>(GetWorld(), WidgetClass);
	if (PlayAgainWidget)
	{
		PlayAgainWidget->SetText("You Died");
		PlayAgainWidget->AddToViewport();
	}
}

void ADreamateTestTaskGameModeBase::Victory()
{
	PlayAgainWidget = CreateWidget<UPlayAgainWidget>(GetWorld(), WidgetClass);
	if (PlayAgainWidget)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, TEXT("Victory"));
		PlayAgainWidget->SetText("You Won");
		PlayAgainWidget->AddToViewport();
	}
}
