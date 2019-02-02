#include "EscapeGameGameState.h"

AEscapeGameGameState::AEscapeGameGameState()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> BP_ItemDB(TEXT("DataTable'/Game/Data/ItemDB.ItemDB'"));
	ItemDB = BP_ItemDB.Object;
}

UDataTable* AEscapeGameGameState::GetItemDB() const
{
	return ItemDB;
}