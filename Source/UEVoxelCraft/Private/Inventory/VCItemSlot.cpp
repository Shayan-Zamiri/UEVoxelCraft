// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/VCItemSlot.h"
#include "Inventory/VCItemDataAsset.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

UVCItemSlot::UVCItemSlot() : SlotNumber{0}, SlotItemCount{0}, Item{nullptr}
{
}

// FUNCTIONS

bool UVCItemSlot::IsSlotValid() const { return SlotNumber >= 0 && SlotItemType.IsValid(); }

bool UVCItemSlot::IsSlotEmpty() const { return SlotItemCount == 0 && !IsValid(Item); }

int32 UVCItemSlot::GetSlotMaxCount() const { return IsValid(Item) ? Item->GetMaxItemCount() : 0; }

void UVCItemSlot::EmptySlot()
{
	SetSlotItemCount(0);
	SetItem(nullptr);
}

void UVCItemSlot::FillSlot(const UVCItemDataAsset* InItemDA)
{
	if (IsValid(InItemDA))
	{
		SetItem(InItemDA);
		SetSlotItemCount(InItemDA->GetMaxItemCount());
	}
	else if (IsValid(Item))
	{
		SetSlotItemCount(Item->GetMaxItemCount());
	}
}

// GETTERS & SETTERS

int32 UVCItemSlot::GetSlotNumber() const { return SlotNumber; }

void UVCItemSlot::SetSlotNumber(int32 InSlotNum) { SlotNumber = InSlotNum < 0 ? 0 : InSlotNum; }

int32 UVCItemSlot::GetSlotItemCount() const { return SlotItemCount; }

void UVCItemSlot::SetSlotItemCount(int32 InSlotItemCount) { SlotItemCount = FMath::Clamp(InSlotItemCount, 0, GetSlotMaxCount()); }

const FPrimaryAssetType& UVCItemSlot::GetSlotItemType() const { return SlotItemType; }

void UVCItemSlot::SetSlotItemType(const FPrimaryAssetType& InSlotItemType) { SlotItemType = InSlotItemType; }

const UVCItemDataAsset* UVCItemSlot::GetItem() const { return Item; }

void UVCItemSlot::SetItem(const UVCItemDataAsset* InItemDA) { Item = InItemDA; }
