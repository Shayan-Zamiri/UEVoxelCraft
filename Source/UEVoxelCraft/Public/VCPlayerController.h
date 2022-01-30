// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VCPlayerController.generated.h"

class AVCHUD;

UCLASS()
class UEVOXELCRAFT_API AVCPlayerController : public APlayerController
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
protected:
	virtual void BeginPlay() override;

	// FUNCTIONS
public:
	void GetCrosshairLocationAndDirection(FVector& OutWorldLocation, FVector& OutWorldDirection) const;

	// GETTERS && SETTERS
	AVCHUD* GetVCHUD();

	// PROPERTIES
	TWeakObjectPtr<AVCHUD> VCHUD;
};
