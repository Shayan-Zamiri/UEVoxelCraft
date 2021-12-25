// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VoxelCharacter.generated.h"

class UCameraComponent;

UCLASS()
class AVoxelCharacter : public ACharacter
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	// Sets default values for this character's properties
	AVoxelCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// FUNCTIONS
private:
	UFUNCTION()
	void MoveForward(float InVal);

	UFUNCTION()
	void MoveRight(float InVal);

	// PROPERTIES
private:
	UPROPERTY()
	UCameraComponent* PlayerCamera;
};
