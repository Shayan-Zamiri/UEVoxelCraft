// Fill out your copyright notice in the Description page of Project Settings.


#include "VCCheatManager.h"

#include "VCCharacter.h"
#include "VCInventoryComponent.h"
#include "VCItemDataAsset.h"
#include "Kismet/GameplayStatics.h"

// FUNCTIONS

void UVCCheatManager::ForceGC() const
{
	GEngine->ForceGarbageCollection(true);
}

void UVCCheatManager::AddItemToInventory(FString Item, int32 Count) const
{
	AVCCharacter* Character = Cast<AVCCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Character)
		return;

	const FPrimaryAssetId ItemID{UVCAssetManager::InventoryItem, FName{Item}};
	Character->InventoryComp->AddItem(ItemID, Count);
}

void UVCCheatManager::SpawnItem(int32 SlotNumber) const
{
	AVCCharacter* Character = Cast<AVCCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Character)
		return;

	const UVCItemDataAsset* Item = Character->InventoryComp->GetItem(SlotNumber);
	if (IsValid(Item))
	{
		const FVector Forward = Character->GetActorForwardVector();
		GetWorld()->SpawnActor<AActor>(Item->GetItemClass(), Character->GetActorLocation() + Forward * 150.0f, FRotator{});
	}
}
