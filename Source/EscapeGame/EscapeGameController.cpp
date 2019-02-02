// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapeGameController.h"
#include "EscapeGameGameState.h"
#include "EscapeGameCharacter.h"

AEscapeGameController::AEscapeGameController()
{
	InventorySlotLimit = 50;
	InventoryWeightLimit = 5000;
}

int32 AEscapeGameController::GetInventoryWeight()
{
	int32 Weight = 0;
	for (auto& Item : Inventory)
	{
		Weight += Item.Weight;
	}

	return Weight;
}


bool AEscapeGameController::AddItemToInventoryByID(FName ID)
{
	AEscapeGameGameState* GameState = Cast<AEscapeGameGameState>(GetWorld()->GetGameState());
	UDataTable* ItemTable = GameState->GetItemDB();
	FInventoryItem* ItemToAdd = ItemTable->FindRow<FInventoryItem>(ID, "");

	if (ItemToAdd)
	{
		if (Inventory.Num() < InventorySlotLimit && GetInventoryWeight() + ItemToAdd->Weight <= InventoryWeightLimit)
		{
			Inventory.Add(*ItemToAdd);
			ReloadInventory();
			return true;
		}
	}
	return false;
}

void AEscapeGameController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Interact", IE_Pressed, this, &AEscapeGameController::Interact);
}

void AEscapeGameController::Interact()
{
	if (CurrentInteractable)
	{
		CurrentInteractable->Interact(this);
	}
}