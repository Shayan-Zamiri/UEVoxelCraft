// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VCTypes.h"
#include "GameFramework/Character.h"
#include "UObject/StrongObjectPtr.h"
#include "VCCharacter.generated.h"

class UCameraComponent;
class AVCBaseBlock;
class AVCPlayerController;
class AVCVoxelChunk;

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
	void AddBlock();

	UFUNCTION()
	void RemoveBlock();

	UFUNCTION()
	void MoveForward(float InVal);

	UFUNCTION()
	void MoveRight(float InVal);

	/** returns nullptr if doesn't hit anything */
	AVCVoxelChunk* LineTraceChunk(const FVector& InTargetPoint, FVector& OutLocation, FVector& OutNormal) const;

	// PROPERTIES
protected:
	/** This is just for test, we will add inventory */
	UPROPERTY(EditAnywhere, Category= "Properties")
	EVCBlockType BlockToSpawn = EVCBlockType::Dirt;

	UPROPERTY(EditAnywhere, Category= "Properties")
	float BlockSpawnDistance;

private:
	UPROPERTY()
	TWeakObjectPtr<AVCPlayerController> VCPlayerController;

	UPROPERTY(EditAnywhere, Category= "Properties|Components")
	UCameraComponent* CameraComp;
};
