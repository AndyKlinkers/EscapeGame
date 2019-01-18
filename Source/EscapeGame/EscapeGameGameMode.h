// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "EscapeGameGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API AEscapeGameGameMode : public AGameMode
{
	GENERATED_BODY()
	AEscapeGameGameMode(const FObjectInitializer& ObjectInitializer);
	virtual void StartPlay() override;

};
