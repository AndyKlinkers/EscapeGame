#pragma once

#include "Engine.h"
#include "GameFramework/GameStateBase.h"
#include "EscapeGameGameState.generated.h"

UCLASS()
class ESCAPEGAME_API AEscapeGameGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AEscapeGameGameState();

	UDataTable* GetItemDB() const;

protected:
	UPROPERTY(EditDefaultsOnly)
	class UDataTable* ItemDB;
};
