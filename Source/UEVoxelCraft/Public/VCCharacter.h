// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VCCharacter.generated.h"

class UCameraComponent;

UCLASS()
class AVCCharacter : public ACharacter
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AVCCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
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
