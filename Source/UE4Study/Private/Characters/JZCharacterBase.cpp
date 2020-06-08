// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/JZCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"

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
}

void AJZCharacterBase::MoveRight(float Value)
{
}

void AJZCharacterBase::TurnRightAtRate(float Value)
{
}

void AJZCharacterBase::LookUpAtRate(float Value)
{
}

// Called to bind functionality to input
void AJZCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AJZCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJZCharacterBase::MoveRight);

	PlayerInputComponent->BindAxis("TurnRight", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRightAtRate", this, &AJZCharacterBase::TurnRightAtRate);
	PlayerInputComponent->BindAxis("LookUpAtRate", this, &AJZCharacterBase::LookUpAtRate);
}