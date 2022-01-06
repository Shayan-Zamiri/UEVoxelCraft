// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VCHUD.generated.h"

UCLASS(Blueprintable)
class UEVOXELCRAFT_API AVCHUD : public AHUD
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AVCHUD() = default;
	virtual ~AVCHUD() override = default;

	virtual void DrawHUD() override;

	// PROPERTIES
private:
	UPROPERTY(EditAnywhere, Category= "Properties")
	UTexture2D* CrosshairTex;
};
