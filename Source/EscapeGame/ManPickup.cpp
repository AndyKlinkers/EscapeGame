#include "ManPickup.h"
#include "EscapeGameController.h"

AManPickup::AManPickup()
{
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	RootComponent = Cast<USceneComponent>(PickupMesh);

	ItemID = FName("No ID");

	Super::Name = "Item";
	Super::Action = "pickup";
}

void AManPickup::Interact_Implementation(APlayerController* Controller)
{
	Super::Interact_Implementation(Controller);

	AEscapeGameController* IController = Cast<AEscapeGameController>(Controller);
	if(IController->AddItemToInventoryByID(ItemID))
		Destroy();
}