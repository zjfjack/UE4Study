// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JZCharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;

UCLASS()
class UE4STUDY_API AJZCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJZCharacterBase();

protected:

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnRightAtRate(float Value);
	void LookUpAtRate(float Value);
	void Interact();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRightRate = 45.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpAtRate = 45.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	float TraceDistance = 2000.f;

	UFUNCTION(BlueprintNativeEvent)
	void TraceFoward();
	void TraceFoward_Implementation();

public:
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	UStaticMeshComponent* MeshComp = nullptr;

private:
	AActor* FocusedActor = nullptr;

	void OnLineTraceHitActor(AActor* Interactable);
	void OnInteract(AActor* Actor);
	void StartFocus(AActor* Actor);
	void EndFocus(AActor* Actor);
};
