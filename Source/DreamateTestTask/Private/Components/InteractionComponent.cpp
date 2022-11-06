// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionComponent.h"

#include "InteractableObjects/InteractionInterface.h"
#include "Inventory/InventoryComponent.h"
#include "Inventory/InventoryInterface.h"


// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{

}

void UInteractionComponent::Interact()
{
	TArray<AActor*> OverlappingActors;
	const TSubclassOf<AActor> ClassFilter;
	GetOwner()->GetOverlappingActors(OverlappingActors, ClassFilter);
	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (IInteractionInterface* Interactable = Cast<IInteractionInterface>(OverlappingActor))
		{
			UObject* InteractedObject = Interactable->OnInteraction();
			if (InteractedObject)
			{
				HandleInteractedObject(InteractedObject);
			}
			break;
		}
	}
}

void UInteractionComponent::HandleInteractedObject(UObject* InteractedObject)
{
	UItemData* ItemData = Cast<UItemData>(InteractedObject);
	if (ItemData)
	{
		IInventoryInterface* Inventory = Cast<IInventoryInterface>(GetOwner());
		if (Inventory)
		{
			Inventory->GetInventoryComponent()->AddInventoryItem(ItemData);
		}
	}
}