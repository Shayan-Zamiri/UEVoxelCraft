// Fill out your copyright notice in the Description page of Project Settings.


#include "VCItemSlot.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

UVCItemSlot::UVCItemSlot() : SlotNumber{0}, SlotMaxCount{0}, SlotItemCount{0}
{
}

UVCItemSlot::UVCItemSlot(const FPrimaryAssetType InSlotItemType, const uint8 InSlotNumber) : SlotNumber{InSlotNumber}, SlotMaxCount{0}, SlotItemCount{0}, SlotItemType{InSlotItemType}
{
}

UVCItemSlot::UVCItemSlot(const uint8 InSlotNumber, const uint8 InSlotMaxCount, const FPrimaryAssetType& InItemType) : SlotNumber{InSlotNumber}, SlotMaxCount{InSlotMaxCount},
                                                                                                                      SlotItemCount{0}, SlotItemType{InItemType}
{
}

// FUNCTIONS

bool UVCItemSlot::IsSlotValid() const { return SlotNumber > 0 && SlotMaxCount > 0 && SlotItemType.IsValid(); }

bool UVCItemSlot::IsSlotEmpty() const { return SlotItemCount == 0; }

// GETTERS & SETTERS

uint8 UVCItemSlot::GetSlotNumber() const { return SlotNumber; }

void UVCItemSlot::SetSlotNumber(uint8 InSlotNum) { SlotNumber = InSlotNum; }

uint8 UVCItemSlot::GetSlotMaxCount() const { return SlotMaxCount; }

void UVCItemSlot::SetSlotMaxCount(uint8 InSlotMaxCount) { SlotMaxCount = InSlotMaxCount; }

uint8 UVCItemSlot::GetSlotItemCount() const { return SlotItemCount; }

void UVCItemSlot::SetSlotItemCount(uint8 InSlotItemCount) { SlotItemCount = InSlotItemCount; }

const FPrimaryAssetType& UVCItemSlot::GetSlotItemType() const { return SlotItemType; }

void UVCItemSlot::SetSlotItemType(const FPrimaryAssetType& InSlotItemType) { SlotItemType = InSlotItemType; }
