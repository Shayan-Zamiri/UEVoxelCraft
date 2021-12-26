// Fill out your copyright notice in the Description page of Project Settings.


#include "VCCharacter.h"
#include "Camera/CameraComponent.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

// Sets default values
AVCCharacter::AVCCharacter() : PlayerCamera{nullptr}
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PlayerCamera->SetupAttachment(RootComponent);

	/** To rotate the camera with the movement of the mouse(which rotates player controller) */
	PlayerCamera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AVCCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AVCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Axis
	PlayerInputComponent->BindAxis("MoveForward", this, &AVCCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVCCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Lookup", this, &ACharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);

	// Action
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}

// FUNCTIONS

void AVCCharacter::MoveForward(float InVal)
{
	AddMovementInput(GetActorForwardVector(), InVal);
}

void AVCCharacter::MoveRight(float InVal)
{
	AddMovementInput(GetActorRightVector(), InVal);
}
