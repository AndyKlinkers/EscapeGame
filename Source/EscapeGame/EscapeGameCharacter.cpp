// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapeGameCharacter.h"
#include "Interactable.h"
#include "ManPickup.h"
#include "InventoryItem.h"
#include "EscapeGameController.h"


// Sets default values
AEscapeGameCharacter::AEscapeGameCharacter(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(RootComponent);
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;



	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->SetCastShadow(true);


}

// Called when the game starts or when spawned
void AEscapeGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->SetCastShadow(true);
	DefaultMaxWalkingSpeed = GetCharacterMovement()->MaxWalkSpeed;

}

// Called every frame
void AEscapeGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckForInteractables();


}

// Called to bind functionality to input
void AEscapeGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AEscapeGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEscapeGameCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookHorizontal", this, &AEscapeGameCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookVertical", this, &AEscapeGameCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &AEscapeGameCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &AEscapeGameCharacter::StopSprint);
}

void AEscapeGameCharacter::MoveForward(float Val)
{
	if (Controller && Val != 0.0f)
	{

		/*FRotator Rotation = Controller->GetControlRotation();

		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			//niet draaien in de Y-as
			Rotation.Pitch = 0.0f;
		}

		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		*/
		AddMovementInput(GetActorForwardVector(), Val);
		
	}
}

void AEscapeGameCharacter::MoveRight(float Val)
{
	if ((Controller != NULL) && (Val != 0.0f))
	{

		/*const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		*/
		AddMovementInput(GetActorRightVector(), Val);
	}
}

void AEscapeGameCharacter::StartSprint()
{
	bSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkingSpeed * SprintModifier;
}
void AEscapeGameCharacter::StopSprint()
{
	bSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkingSpeed;
}


void AEscapeGameCharacter::CheckForInteractables()
{
	// Create a LineTrace to check for a hit
	FHitResult HitResult;

	int32 Range = 5000;
	FVector StartTrace = FirstPersonCameraComponent->GetComponentLocation();
	FVector EndTrace = (FirstPersonCameraComponent->GetForwardVector() * Range) + StartTrace;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	AEscapeGameController* IController = Cast<AEscapeGameController>(GetController());

	if (IController)
	{
		// Check if something is hit
		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, QueryParams))
		{
			// Cast the actor to AInteractable
			AInteractable* Interactable = Cast<AInteractable>(HitResult.GetActor());
			// If the cast is successful
			if (Interactable)
			{
				IController->CurrentInteractable = Interactable;
				return;
			}
		}

		IController->CurrentInteractable = nullptr;
	}
}
