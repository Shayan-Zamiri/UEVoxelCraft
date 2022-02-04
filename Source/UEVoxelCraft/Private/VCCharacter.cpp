// Fill out your copyright notice in the Description page of Project Settings.


#include "VCCharacter.h"

#include "VCPlayerController.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Inventory/VCInventoryComponent.h"
#include "Procedural/VCVoxelChunk.h"
#include "GameFramework/HUD.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

AVCCharacter::AVCCharacter() : BlockSpawnDistance{300.0f}, bInUI{false}, VCPlayerController{nullptr}
{
	PrimaryActorTick.bCanEverTick = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);
	// To rotate the camera with the movement of the mouse(which rotates player controller)
	CameraComp->bUsePawnControlRotation = true;

	InventoryComp = CreateDefaultSubobject<UVCInventoryComponent>(TEXT("InventoryComp"));
}

void AVCCharacter::BeginPlay()
{
	Super::BeginPlay();

	VCPlayerController = Cast<AVCPlayerController>(GetWorld()->GetFirstPlayerController());
	checkf(VCPlayerController.IsValid(), TEXT("Can't set PlayerController weak reference in the Character"));
}

void AVCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Action
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("AddBlock", IE_Pressed, this, &AVCCharacter::AddBlock);
	PlayerInputComponent->BindAction("RemoveBlock", IE_Pressed, this, &AVCCharacter::RemoveBlock);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AVCCharacter::ShowHideInventory);

	// Axis
	PlayerInputComponent->BindAxis("MoveForward", this, &AVCCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVCCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Lookup", this, &AVCCharacter::Turn);
	PlayerInputComponent->BindAxis("Turn", this, &AVCCharacter::LookUp);
}

// FUNCTIONS

void AVCCharacter::AddBlock()
{
	FVector Location{}, Direction{}, Normal{};
	VCPlayerController->GetCrosshairLocationAndDirection(Location, Direction);
	const FVector TargetPoint{Location + BlockSpawnDistance * Direction};
	AVCVoxelChunk* Chunk = LineTraceChunk(TargetPoint, Location, Normal);
	if (IsValid(Chunk)) { Chunk->ModifyChunkMesh(AVCVoxelChunk::WorldLocationToBlockLocalPosition(Location + Normal), BlockToSpawn); }
}

void AVCCharacter::RemoveBlock()
{
	FVector Location{}, Direction{}, Normal{};
	VCPlayerController->GetCrosshairLocationAndDirection(Location, Direction);
	const FVector TargetPoint{Location + BlockSpawnDistance * Direction};
	AVCVoxelChunk* Chunk = LineTraceChunk(TargetPoint, Location, Normal);
	if (IsValid(Chunk))
	{
		Chunk->ModifyChunkMesh(AVCVoxelChunk::WorldLocationToBlockLocalPosition(Location - Normal), EVCBlockType::None);
	}
}

void AVCCharacter::MoveForward(float InVal) { AddMovementInput(GetActorForwardVector(), InVal); }

void AVCCharacter::MoveRight(float InVal) { AddMovementInput(GetActorRightVector(), InVal); }

void AVCCharacter::Turn(float InVal)
{
	if (!bInUI)
	{
		AddControllerPitchInput(InVal);
	}
}

void AVCCharacter::LookUp(float InVal)
{
	if (!bInUI)
	{
		AddControllerYawInput(InVal);
	}
}

void AVCCharacter::ShowHideInventory()
{
	if (!bInUI)
	{
		InventoryComp->ShowInventory();
		bInUI = true;
		VCPlayerController->SetShowMouseCursor(true);
	}
	else
	{
		InventoryComp->HideInventory();
		bInUI = false;
		VCPlayerController->SetShowMouseCursor(false);
	}
	VCPlayerController.Get()->GetHUD()->ShowHUD();
}

AVCVoxelChunk* AVCCharacter::LineTraceChunk(const FVector& InTargetPoint, FVector& OutLocation, FVector& OutNormal) const
{
	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, CameraComp->GetComponentLocation(), InTargetPoint, ECC_Visibility))
	{
		DrawDebugLine(GetWorld(), CameraComp->GetComponentLocation(), InTargetPoint, FColor::Green, false,
		              1.0f, 0, 1.0f);
	}
	else
	{
		DrawDebugLine(GetWorld(), CameraComp->GetComponentLocation(), InTargetPoint, FColor::Red, false,
		              1.0f, 0, 1.0f);
	}

	OutLocation = HitResult.Location;
	OutNormal = HitResult.Normal;

	return Cast<AVCVoxelChunk>(HitResult.Actor);
}
