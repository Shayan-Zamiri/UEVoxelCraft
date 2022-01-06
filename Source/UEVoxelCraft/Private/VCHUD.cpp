// Fill out your copyright notice in the Description page of Project Settings.


#include "VCHUD.h"

#include "Engine/Canvas.h"

void AVCHUD::DrawHUD()
{
	Super::DrawHUD();

	// Didn't use a check() so you can play the game without a crosshair
	if (CrosshairTex->IsValidLowLevel())
	{
		FVector2D Center{Canvas->ClipX / 2, Canvas->ClipY / 2};

		FCanvasTileItem TileItem{Center, CrosshairTex->Resource, FLinearColor::Red};
		TileItem.BlendMode = SE_BLEND_Translucent;

		Canvas->DrawItem(TileItem);
	}
}
