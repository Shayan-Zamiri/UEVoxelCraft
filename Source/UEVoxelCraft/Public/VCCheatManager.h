// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "VCCheatManager.generated.h"

UENUM()
enum class EItem : uint8
{
	Axe,
	Shovel
};

UCLASS(Within= VCPlayerController)
class UEVOXELCRAFT_API UVCCheatManager : public UCheatManager
{
	GENERATED_BODY()

	// FUNCTIONS
public:
	/** Runs a garbage collection */
	UFUNCTION(Exec)
	void ForceGC();

	UFUNCTION(Exec)
	void AddItemToInventory(EItem Item, int32 Count);
};
