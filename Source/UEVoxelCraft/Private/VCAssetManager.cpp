// Fill out your copyright notice in the Description page of Project Settings.


#include "VCAssetManager.h"

// STATICS

const FPrimaryAssetType UVCAssetManager::InventoryItem = TEXT("InventoryItem");

// GETTERS & SETTERS

UVCAssetManager& UVCAssetManager::Get()
{
	UVCAssetManager* VCAssetManager = Cast<UVCAssetManager>(GEngine->AssetManager);
	if(VCAssetManager)
	{
		return *VCAssetManager;
	}

	UE_LOG(LogTemp, Fatal, TEXT("Failed to get VCAssetManager"));
	return *NewObject<UVCAssetManager>();
}
