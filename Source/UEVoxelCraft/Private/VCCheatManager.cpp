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

void UVCCheatManager::SpawnItemFromInventory(int32 SlotNumber) const
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

void UVCCheatManager::RemoveItemFromInventorySlot(int32 SlotNumber) const
{
	AVCCharacter* Character = Cast<AVCCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Character)
		return;

	if (SlotNumber < Character->InventoryComp->SlotCount && SlotNumber >= 0)
		Character->InventoryComp->RemoveItemFromSlot(SlotNumber);
}

void UVCCheatManager::PrintInventoryData() const
{
	AVCCharacter* Character = Cast<AVCCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Character)
		return;

	for (const auto& It : Character->InventoryComp->InventoryData)
	{
		FString Text = It.Key.ToString() + " " + FString::FromInt(It.Value->GetItemCount());
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, Text, false);
	}
}
