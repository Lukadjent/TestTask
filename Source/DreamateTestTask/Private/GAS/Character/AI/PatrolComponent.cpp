// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Character/AI/PatrolComponent.h"

UPatrolComponent::UPatrolComponent()
{
	
}

TArray<ATargetPoint*> UPatrolComponent::GetPatrolPoints() const
{
	return PatrolPoints;
}