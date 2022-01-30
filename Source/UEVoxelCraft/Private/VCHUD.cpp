// Fill out your copyright notice in the Description page of Project Settings.


#include "VCHUD.h"
#include "Engine/Canvas.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

AVCHUD::AVCHUD() : CrosshairX{0.0f}, CrosshairY{0.0f}, CrosshairXLocation{0.5f}, CrosshairYLocation{0.5f}
{
}

void AVCHUD::DrawHUD()
{
	Super::DrawHUD();

	// Didn't use a check() so you can play the game without a crosshair
	if (CrosshairTex->IsValidLowLevel())
	{
		CrosshairX = Canvas->SizeX * CrosshairXLocation;
		CrosshairY = Canvas->SizeY * CrosshairYLocation;
		DrawTexture(CrosshairTex, CrosshairX - 25.0f, CrosshairY - 25.0f, 50.0f, 50.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	}
}

float AVCHUD::GetCrosshairX() const { return CrosshairX; }

float AVCHUD::GetCrosshairY() const { return CrosshairY; }
