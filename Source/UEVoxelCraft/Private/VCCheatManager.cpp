// Fill out your copyright notice in the Description page of Project Settings.


#include "VCCheatManager.h"

#include "VCCharacter.h"
#include "VCInventoryComponent.h"
#include "Kismet/GameplayStatics.h"

// FUNCTIONS

void UVCCheatManager::ForceGC()
{
	GEngine->ForceGarbageCollection(true);
}

void UVCCheatManager::AddItemToInventory(EItem Item, int32 Count)
{
	AVCCharacter* Character = Cast<AVCCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Character)
		return;

	const FPrimaryAssetId ItemID = FPrimaryAssetId{UVCAssetManager::InventoryItem, FName{"Axe"}};
	Character->InventoryComp->AddItem(ItemID, Count);
	Character->InventoryComp->UpdateInventoryUI();
}
