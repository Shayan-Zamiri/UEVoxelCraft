// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelCharacter.h"
#include "Camera/CameraComponent.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

// Sets default values
AVoxelCharacter::AVoxelCharacter() : PlayerCamera{nullptr}
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PlayerCamera->SetupAttachment(RootComponent);

	/** To rotate the camera with the movement of the mouse(which rotates player controller) */
	PlayerCamera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AVoxelCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVoxelCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AVoxelCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Axis
	PlayerInputComponent->BindAxis("MoveForward", this, &AVoxelCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVoxelCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Lookup", this, &ACharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);

	// Action
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}

// FUNCTIONS

void AVoxelCharacter::MoveForward(float InVal)
{
	AddMovementInput(GetActorForwardVector(), InVal);
}

void AVoxelCharacter::MoveRight(float InVal)
{
	AddMovementInput(GetActorRightVector(), InVal);
}
