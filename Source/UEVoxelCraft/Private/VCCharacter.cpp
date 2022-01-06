// Fill out your copyright notice in the Description page of Project Settings.


#include "VCCharacter.h"

#include "VCBaseBlock.h"
#include "VCPlayerController.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

AVCCharacter::AVCCharacter() : BlockSpawnDistance{300.0f}, VCPlayerController{nullptr}, BlockClassToSpawn{nullptr}
{
	PrimaryActorTick.bCanEverTick = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);

	// To rotate the camera with the movement of the mouse(which rotates player controller)
	CameraComp->bUsePawnControlRotation = true;
}

void AVCCharacter::BeginPlay()
{
	Super::BeginPlay();

	VCPlayerController = Cast<AVCPlayerController>(GetWorld()->GetFirstPlayerController());
	checkf(VCPlayerController.IsValid(), TEXT("Can't set PlayerController weak reference in the Character"));
}

void AVCCharacter::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void AVCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Action
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AVCCharacter::Action);

	// Axis
	PlayerInputComponent->BindAxis("MoveForward", this, &AVCCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVCCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Lookup", this, &ACharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
}

// FUNCTIONS

void AVCCharacter::Action()
{
	FVector Location{}, Direction{};
	VCPlayerController->GetCrosshairLocationAndDirection(Location, Direction);
	const FVector TargetPoint{Location + BlockSpawnDistance * Direction};
	FVector Normal{};
	AVCBaseBlock* HitBlock = nullptr;
	const bool bDoesHit = LineTraceBlock(TargetPoint, Location, Normal, HitBlock);
	if (bDoesHit && IsValid(HitBlock))
	{
		GetWorld()->SpawnActor<AVCBaseBlock>(BlockClassToSpawn, AVCBaseBlock::GetAttachLocation(Location, Normal), FRotator{});
	}
}

void AVCCharacter::MoveForward(float InVal) { AddMovementInput(GetActorForwardVector(), InVal); }

void AVCCharacter::MoveRight(float InVal) { AddMovementInput(GetActorRightVector(), InVal); }

bool AVCCharacter::LineTraceBlock(const FVector& InTargetPoint, FVector& OutLocation, FVector& OutNormal,
                                  AVCBaseBlock*& OutHitBlock) const
{
	FHitResult HitResult;
	const bool bDoesHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraComp->GetComponentLocation(), InTargetPoint,
	                                                           ECC_Visibility);

	if (bDoesHit)
	{
		DrawDebugLine(GetWorld(), CameraComp->GetComponentLocation(), InTargetPoint, FColor::Green, false,
		              1.0f, 0, 1.0f);
	}
	else
	{
		DrawDebugLine(GetWorld(), CameraComp->GetComponentLocation(), InTargetPoint, FColor::Red, false,
		              1.0f, 0, 1.0f);
		return false;
	}

	OutLocation = HitResult.Location;
	OutNormal = HitResult.Normal;
	OutHitBlock = Cast<AVCBaseBlock>(HitResult.Actor.Get());

	if (!OutHitBlock)
		return false;

	return true;
}
