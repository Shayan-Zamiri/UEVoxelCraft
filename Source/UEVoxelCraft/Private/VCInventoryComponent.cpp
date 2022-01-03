// Fill out your copyright notice in the Description page of Project Settings.


#include "VCInventoryComponent.h"
#include "VCItemSlot.h"
#include "VCItemDataAsset.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS 

UVCInventoryComponent::UVCInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UVCInventoryComponent::~UVCInventoryComponent()
{
	ItemsStrongReferences.Empty();
	ItemSlotsStrongReferences.Empty();
	InventorySlots.Empty();
	InventoryData.Empty();
}

void UVCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

// FUNCTIONS

void UVCInventoryComponent::DecreaseItemSlotCount(UVCItemSlot* InItemSlot, uint8 InCount)
{
	check(InItemSlot)
	InItemSlot->SetSlotItemCount(InCount == 0 ? 0 : InItemSlot->GetSlotItemCount() - InCount);
	if(InItemSlot->GetSlotItemCount() == 0)
	{
		UVCItemDataAsset*& Item = InventorySlots.FindChecked(InItemSlot->GetSlotNumber()).Value;
		// Subtract from the total number of that item in inventory
		uint8& Count = InventoryData.FindChecked(Item);
		Count -= InCount;
		Item = nullptr;
	}
}
