// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "VCCheatManager.generated.h"

UCLASS(Within= VCPlayerController)
class UEVOXELCRAFT_API UVCCheatManager : public UCheatManager
{
	GENERATED_BODY()

	// FUNCTIONS
public:
	/** Runs a garbage collection */
	UFUNCTION(Exec)
	void ForceGC() const;

	UFUNCTION(Exec)
	void AddItemToInventory(FString Item, int32 Count) const;

	UFUNCTION(Exec)
	void SpawnItem(int32 SlotNumber) const;
};
