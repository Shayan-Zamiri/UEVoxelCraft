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
	AVCHUD();
	virtual ~AVCHUD() override = default;

	virtual void DrawHUD() override;

	// PROPERTIES
private:
	UPROPERTY(VisibleAnywhere, Category= "Properties")
	float CrosshairX;
	
	UPROPERTY(VisibleAnywhere, Category= "Properties")
	float CrosshairY;
	
	UPROPERTY(EditAnywhere, Category= "Properties")
	float CrosshairXLocation;
	
	UPROPERTY(EditAnywhere, Category= "Properties")
	float CrosshairYLocation;
	
	UPROPERTY(EditAnywhere, Category= "Properties")
	UTexture2D* CrosshairTex;
};
