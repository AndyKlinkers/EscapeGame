// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeGameCharacter.h"

// Sets default values
AEscapeGameCharacter::AEscapeGameCharacter(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(RootComponent);
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void AEscapeGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEscapeGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEscapeGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AEscapeGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEscapeGameCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookHorizontal", this, &AEscapeGameCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookVertical", this, &AEscapeGameCharacter::AddControllerPitchInput);

}

void AEscapeGameCharacter::MoveForward(float Val)
{
	if ((Controller != NULL) && (Val != 0.0f))
	{

		FRotator Rotation = Controller->GetControlRotation();

		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			//niet draaien in de Y-as
			Rotation.Pitch = 0.0f;
		}

		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Val);
	}
}

void AEscapeGameCharacter::MoveRight(float Val)
{
	if ((Controller != NULL) && (Val != 0.0f))
	{

		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);

		AddMovementInput(Direction, Val);
	}
}

