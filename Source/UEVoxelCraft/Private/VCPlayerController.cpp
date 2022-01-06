// Fill out your copyright notice in the Description page of Project Settings.


#include "VCPlayerController.h"
#include "VCHUD.h"


void AVCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	VCHUD = Cast<AVCHUD>(GetHUD());
	checkf(VCHUD.IsValid(), TEXT("Can't set HUD weak reference in the Character"));
}

void AVCPlayerController::GetCrosshairLocationAndDirection(FVector& OutWorldLocation, FVector& OutWorldDirection) const
{
	DeprojectScreenPositionToWorld(VCHUD->GetCrosshairX(), VCHUD->GetCrosshairY(), OutWorldLocation, OutWorldDirection);
}

AVCHUD* AVCPlayerController::GetVCHUD() { return VCHUD.Get(); }
