// Fill out your copyright notice in the Description page of Project Settings.


#include "VCItemSlot.h"

#include "VCItemDataAsset.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

UVCItemSlot::UVCItemSlot() : SlotNumber{0}, SlotItemCount{0}
{
}

UVCItemSlot::UVCItemSlot(const FPrimaryAssetType InSlotItemType, const uint8 InSlotNumber)
	: SlotNumber{InSlotNumber}, SlotItemCount{0}, SlotItemType{InSlotItemType}
{
}

UVCItemSlot::UVCItemSlot(const uint8 InSlotNumber, const uint8 InSlotMaxCount, const FPrimaryAssetType& InItemType)
	: SlotNumber{InSlotNumber}, SlotItemCount{0}, SlotItemType{InItemType}
{
}

// FUNCTIONS

bool UVCItemSlot::IsSlotValid() const { return SlotNumber > 0 && SlotItemType.IsValid(); }

bool UVCItemSlot::IsSlotEmpty() const
{
	checkf(IsSlotValid(), TEXT("%d isn't valid"), SlotNumber);
	return SlotItemCount == 0 && ItemReference.IsValid();
}

// GETTERS & SETTERS

int32 UVCItemSlot::GetSlotNumber() const { return SlotNumber; }

void UVCItemSlot::SetSlotNumber(int32 InSlotNum) { SlotNumber = InSlotNum; }

int32 UVCItemSlot::GetSlotMaxCount() const { return ItemReference.IsValid() ? ItemReference.Get()->GetMaxItemCount() : 0; }

int32 UVCItemSlot::GetSlotItemCount() const { return SlotItemCount; }

void UVCItemSlot::SetSlotItemCount(int32 InSlotItemCount) { SlotItemCount = InSlotItemCount; }

const FPrimaryAssetType& UVCItemSlot::GetSlotItemType() const { return SlotItemType; }

void UVCItemSlot::SetSlotItemType(const FPrimaryAssetType& InSlotItemType) { SlotItemType = InSlotItemType; }

const TWeakObjectPtr<UVCItemDataAsset>& UVCItemSlot::GetItemReference() const { return ItemReference; }

void UVCItemSlot::SetItemReference(UVCItemDataAsset* InOutItemDataAsset) { ItemReference = InOutItemDataAsset; }
