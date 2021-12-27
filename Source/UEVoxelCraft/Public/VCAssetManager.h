// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "VCAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class UEVOXELCRAFT_API UVCAssetManager : public UAssetManager
{
	GENERATED_BODY()

	// GETTERS & SETTERS
	static UVCAssetManager& Get();
	
	// PROPERTIES
public:
	static const FPrimaryAssetType InventoryItem;
};
