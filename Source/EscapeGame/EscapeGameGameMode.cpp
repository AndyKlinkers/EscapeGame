// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeGameGameMode.h"
#include "Engine.h"
#include "string"

AEscapeGameGameMode::AEscapeGameGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void AEscapeGameGameMode::StartPlay()
{
	Super::StartPlay();

	StartMatch();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("HELLO WORLD"));
	}
}


