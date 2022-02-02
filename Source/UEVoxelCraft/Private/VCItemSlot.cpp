// Fill out your copyright notice in the Description page of Project Settings.


#include "VCItemSlot.h"

#include "VCItemDataAsset.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

UVCItemSlot::UVCItemSlot() : SlotNumber{0}, SlotItemCount{0}, Item{nullptr}
{
}

UVCItemSlot::UVCItemSlot(const FPrimaryAssetType& InSlotItemType, int32 SlotNumber)
	: SlotNumber{SlotNumber}, SlotItemCount{0}, SlotItemType{InSlotItemType}, Item{nullptr}
{
}

// FUNCTIONS

bool UVCItemSlot::IsSlotValid() const { return SlotNumber > 0 && SlotItemType.IsValid(); }

bool UVCItemSlot::IsSlotEmpty() const
{
	checkf(IsSlotValid(), TEXT("slot number%d isn't valid"), SlotNumber);
	return SlotItemCount == 0 && IsValid(Item);
}

// GETTERS & SETTERS

int32 UVCItemSlot::GetSlotNumber() const { return SlotNumber; }

void UVCItemSlot::SetSlotNumber(int32 InSlotNum) { SlotNumber = InSlotNum; }

int32 UVCItemSlot::GetSlotMaxCount() const { return IsValid(Item) ? Item->GetMaxItemCount() : 0; }

int32 UVCItemSlot::GetSlotItemCount() const { return SlotItemCount; }

void UVCItemSlot::SetSlotItemCount(int32 InSlotItemCount)
{
	SlotItemCount = InSlotItemCount < 0 ? 1 : InSlotItemCount;
	if (SlotItemCount == 0)
		Item = nullptr;
}

const FPrimaryAssetType& UVCItemSlot::GetSlotItemType() const { return SlotItemType; }

void UVCItemSlot::SetSlotItemType(const FPrimaryAssetType& InSlotItemType) { SlotItemType = InSlotItemType; }

const UVCItemDataAsset* UVCItemSlot::GetItem() const { return Item; }

void UVCItemSlot::SetItem(const UVCItemDataAsset* InOutItemDataAsset) { Item = InOutItemDataAsset; }
