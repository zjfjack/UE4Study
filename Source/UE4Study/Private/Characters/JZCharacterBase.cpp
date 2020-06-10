// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/JZCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"

// Sets default values
AJZCharacterBase::AJZCharacterBase() :
	SpringArmComp(CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"))),
	CameraComp(CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"))),
	MeshComp(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp")))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp);
	MeshComp->SetupAttachment(RootComponent);
}

void AJZCharacterBase::MoveForward(float Value)
{
	if (Controller && Value != 0)
	{
		// GetControlRotation is not GetActorRotation, which is a global rotation
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// YawRotation.Vector() is okay to use here
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// auto Direction1 = GetActorForwardVector().GetSafeNormal();
		// not working, orient rotation to movement is true
		AddMovementInput(Direction, Value);
	}
}

void AJZCharacterBase::MoveRight(float Value)
{
	if (Controller && Value != 0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// YawRotation.Vector() cannot be used here becuase .Vector() is facing the direction (forward)
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// auto Direction1 = GetActorRightVector().GetSafeNormal();  
		// not working, orient rotation to movement is true && forward direction shouldn't affect right vector, it should be global one with camera
		AddMovementInput(Direction, Value);
	}
}

void AJZCharacterBase::TurnRightAtRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRightRate * GetWorld()->GetDeltaSeconds());
}

void AJZCharacterBase::LookUpAtRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpAtRate * GetWorld()->GetDeltaSeconds());
}

void AJZCharacterBase::Interact()
{
	TraceFoward();
}

void AJZCharacterBase::TraceFoward_Implementation()
{
	FVector Location;
	FRotator Rotation;
	FHitResult Hit;
	// Location: CameraComp->GetComponentLocation()
	// Rotation.Vector(): CameraComp->GetForwardVector()
	GetController()->GetPlayerViewPoint(Location, Rotation);
	FVector& Start = Location;
	FVector End = Start + (Rotation.Vector() * TraceDistance);
	FCollisionQueryParams TraceParams;
	                                                                  // Collision presets
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility);

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f);
	if (bHit)
		DrawDebugBox(GetWorld(), Hit.ImpactPoint, FVector(10.f), FColor::Red, false, 2.0f);
}

// Called to bind functionality to input
void AJZCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AJZCharacterBase::Interact);

	PlayerInputComponent->BindAxis("MoveForward", this, &AJZCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJZCharacterBase::MoveRight);

	PlayerInputComponent->BindAxis("TurnRight", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRightRate", this, &AJZCharacterBase::TurnRightAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AJZCharacterBase::LookUpAtRate);
}