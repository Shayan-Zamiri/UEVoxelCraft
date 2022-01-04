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

	InItemSlot->SetSlotItemCount(InCount == 0 ? 0 : InItemSlot->GetSlotItemCount() - InCount);
}

void UVCInventoryComponent::IncreaseItemSlotCount(UVCItemSlot* InItemSlot, uint8 InCount)
{
	check(IsValid(InItemSlot))
	if (InItemSlot->IsSlotEmpty())
		return;
	
	InItemSlot->SetSlotItemCount(InCount == 0 ? InItemSlot->GetItemReference().Get()->GetMaxItemCount() : InItemSlot->GetSlotItemCount() + InCount);
}

void UVCInventoryComponent::InsertInSlot(UVCItemSlot* InItemSlot, UVCItemDataAsset* InItem, uint8 InCount)
{
	check(IsValid(InItemSlot));
	check(IsValid(InItem));
	UVCItemDataAsset*& Item = InventorySlots.FindChecked(InItemSlot->GetSlotNumber()).Value;
	Item = InItem;
	InItemSlot->SetSlotItemCount(InCount);
}

UVCItemSlot* UVCInventoryComponent::FindEmptySlot()
{
	for (auto& It : InventorySlots)
	{
		UVCItemSlot* ItemSlot = It.Value.Key;
		check(IsValid(ItemSlot));
		if (IsSlotEmpty(ItemSlot)) { return ItemSlot; }
	}

	return nullptr;
}

UVCItemSlot* UVCInventoryComponent::FindAppropriateSlot(const FPrimaryAssetId& AssetID)
{
	bool bIsEmptySlotFounded = false;
	UVCItemSlot* ReturnSlot = nullptr;
	for (auto& It : InventorySlots)
	{
		UVCItemDataAsset* Item = It.Value.Value;
		UVCItemSlot* ItemSlot = It.Value.Key;
		check(IsValid(ItemSlot));
		// Appropriate Stackable Slot
		if (Item && Item->GetPrimaryAssetId() == AssetID && ItemSlot->GetSlotItemCount() < ItemSlot->GetSlotMaxCount())
		{
			ReturnSlot = ItemSlot;
			break;
		}
		// Appropriate Empty Slot
		if (!bIsEmptySlotFounded && ItemSlot->GetSlotItemType() == AssetID.PrimaryAssetType && IsSlotEmpty(ItemSlot))
		{
			ReturnSlot = ItemSlot;
			bIsEmptySlotFounded = true;
		}
	}
	return ReturnSlot;
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
		ItemSlot->SetSlotItemCount(It.Key.SlotItemCount);
		ItemsStrongReferences.Add(It.Value);
		ItemSlotsStrongReferences.Add(ItemSlot);
		InventorySlots.Add(ItemSlot->GetSlotNumber(), TPairInitializer<UVCItemSlot*, UVCItemDataAsset*>{ItemSlot, It.Value});
	}
	InventorySlotsEditor.Empty();
}
