// Fill out your copyright notice in the Description page of Project Settings.


#include "VCInventoryComponent.h"
#include "VCItemSlot.h"
#include "VCItemDataAsset.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS 

UVCInventoryComponent::UVCInventoryComponent() { PrimaryComponentTick.bCanEverTick = false; }

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

	InventorySlotsInitializer();
}

// FUNCTIONS

void UVCInventoryComponent::DecreaseItemSlotCount(UVCItemSlot* InItemSlot, uint8 InCount)
{
	check(IsValid(InItemSlot))
	if (InItemSlot->IsSlotEmpty())
		return;

	// Subtract from the total number of that item in InventoryData
	UVCItemDataAsset*& Item = InventorySlots.FindChecked(InItemSlot->GetSlotNumber()).Value;
	checkf(Item, "Slot isn't empty so you should have this item in the InventoryData.");
	uint8* Count = InventoryData.Find(Item);
	checkf(Count, "you have the item so count have to exist in the InventoryData.")
	*Count = InCount == 0 ? *Count - InItemSlot->GetSlotItemCount() : *Count - InCount;

	InItemSlot->SetSlotItemCount(InCount == 0 ? 0 : InItemSlot->GetSlotItemCount() - InCount);
	if (InItemSlot->GetSlotItemCount() == 0) { Item = nullptr; }
}

void UVCInventoryComponent::InsertInSlot(UVCItemSlot* InItemSlot, UVCItemDataAsset* InItem, uint8 InCount)
{
	check(IsValid(InItemSlot));
	check(IsValid(InItem));
	UVCItemDataAsset*& Item = InventorySlots.FindChecked(InItemSlot->GetSlotNumber()).Value;
	Item = InItem;
	InItemSlot->SetSlotItemCount(InItemSlot->GetSlotItemCount() + InCount);
}

UVCItemSlot* UVCInventoryComponent::FindEmptySlot(const FPrimaryAssetType& InSlotItemType)
{
	for (auto It : InventorySlots)
	{
		UVCItemSlot* ItemSlot = It.Value.Key;
		check(IsValid(ItemSlot));
		if (ItemSlot->GetSlotItemType() == InSlotItemType && IsSlotEmpty(ItemSlot)) { return ItemSlot; }
	}

	return nullptr;
}

UVCItemSlot* UVCInventoryComponent::GetSlot(uint8 InSlotNumber)
{
	UVCItemSlot* ItemSlot = InventorySlots.FindChecked(InSlotNumber).Key;
	check(IsValid(ItemSlot));
	return ItemSlot;
}

bool UVCInventoryComponent::IsSlotEmpty(const UVCItemSlot* InItemSlot) const
{
	check(IsValid(InItemSlot));
	return InItemSlot->IsSlotEmpty();
}

bool UVCInventoryComponent::IsSlotValid(const UVCItemSlot* InItemSlot) const
{
	check(IsValid(InItemSlot));
	return InventorySlots.Contains(InItemSlot->GetSlotNumber()) && InItemSlot->IsSlotValid();
}

UVCItemDataAsset* UVCInventoryComponent::GetItem(const UVCItemSlot* InItemSlot)
{
	check(IsValid(InItemSlot));
	UVCItemDataAsset* Item = InventorySlots.FindChecked(InItemSlot->GetSlotNumber()).Value;
	return Item;
}

void UVCInventoryComponent::InventorySlotsInitializer()
{
	for (auto& It : InventorySlotsEditor)
	{
		UVCItemSlot* ItemSlot = NewObject<UVCItemSlot>(this, UVCItemSlot::StaticClass());
		ItemSlot->SetSlotNumber(It.Key.SlotNumber);
		ItemSlot->SetSlotItemType(It.Key.SlotItemType);
		ItemSlot->SetSlotItemCount(It.Key.SlotMaxCount);
		ItemSlot->SetSlotItemCount(It.Key.SlotItemCount);
		ItemsStrongReferences.Add(It.Value);
		ItemSlotsStrongReferences.Add(ItemSlot);
		InventorySlots.Add(ItemSlot->GetSlotNumber(), TPairInitializer<UVCItemSlot*, UVCItemDataAsset*>{ItemSlot, It.Value});
	}
	InventorySlotsEditor.Empty();
}
