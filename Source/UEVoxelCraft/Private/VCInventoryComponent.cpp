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
		uint8* Count = InventoryData.Find(Item);
		if(Count)
		{
			*Count -= InCount;
			Item = nullptr;
		}
	}
}

void UVCInventoryComponent::InsertInSlot(UVCItemSlot* InItemSlot, UVCItemDataAsset* InItem, uint8 InCount)
{
	check(IsValid(InItemSlot));
	check(IsValid(InItem));
	UVCItemDataAsset*& Item = InventorySlots.FindChecked(InItemSlot->GetSlotNumber()).Value;
	Item = InItem;
	// Add to the total number of that item in inventory
	uint8* Count = InventoryData.Find(Item);
	if(Count)
	{
		*Count += InCount;
	}
	// A totally new item
	else
	{
		InventoryData.Add(InItem, InCount);
		ItemsStrongReferences.Add(InItem);
	}

	InItemSlot->SetSlotItemCount(InItemSlot->GetSlotItemCount() + InCount);
}

UVCItemSlot* UVCInventoryComponent::GetSlot(const FPrimaryAssetType& InSlotItemType, uint8 InSlotNumber)
{
	// First checks if it could find the slot by just using	InventorySlots' index
	UVCItemSlot* ItemSlot = InventorySlots.FindChecked(InSlotNumber).Key;
	check(ItemSlot);
	if (ItemSlot->GetSlotItemType() == InSlotItemType)
	{
		return ItemSlot;
	}

	// "Damn it I'll check them all" mode
	for (auto It : InventorySlots)
	{
		ItemSlot = It.Value.Key;
		check(IsValid(ItemSlot));
		if (ItemSlot->GetSlotItemType() == InSlotItemType && ItemSlot->GetSlotNumber() == InSlotNumber)
		{
			return ItemSlot;
		}
	}

	return nullptr;
}
