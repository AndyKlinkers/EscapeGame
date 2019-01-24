// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	if (PressurePlate == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s OpenDoor component: No trigger volume bound"), *GetOwner()->GetName())
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetMassFromPlate() > TriggerMass)
	{
		OnOpen.Broadcast();
	}else {
		OnClose.Broadcast();
	}

	
}

float UOpenDoor::GetMassFromPlate()
{
	float TotalMass = 0;
	TArray<AActor*> OverlappingActorList;
	if (PressurePlate == nullptr)
	{
		return TotalMass;
	}

	PressurePlate->GetOverlappingActors(OUT OverlappingActorList);
	for (auto* CurrentActor : OverlappingActorList)
	{
		
		auto TempMass = CurrentActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		auto vaag = CurrentActor->FindComponentByClass<UPrimitiveComponent>()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("NAME OF class IS (%s)"), *vaag)

		FString Vervaagd(std::to_string(TempMass).c_str());
		UE_LOG(LogTemp, Warning, TEXT("NAME OF ACTOR IS (%s) AND IT's MASS IS (%s)"), *CurrentActor->GetName(), *Vervaagd)

		TotalMass += TempMass;
	}
	return TotalMass;
}

