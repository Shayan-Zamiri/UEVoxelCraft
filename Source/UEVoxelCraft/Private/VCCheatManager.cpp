// Fill out your copyright notice in the Description page of Project Settings.


#include "VCCheatManager.h"

// FUNCTIONS

void UVCCheatManager::ForceGC()
{
	GEngine->ForceGarbageCollection(true);
}
