﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/VCItemDataAsset.h"
#include "VCAssetManager.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

UVCItemDataAsset::UVCItemDataAsset() : MaxItemCount{1}, ItemType{UVCAssetManager::InventoryItem}, ItemClass{nullptr}, ItemIcon{nullptr}
{
}

FPrimaryAssetId UVCItemDataAsset::GetPrimaryAssetId() const { return FPrimaryAssetId(ItemType, ItemName); }

// GETTERS & SETTERS

int32 UVCItemDataAsset::GetItemCount() const { return ItemCount; }

void UVCItemDataAsset::SetItemCount(int32 InItemCount) { ItemCount = InItemCount < 0 ? 0 : InItemCount; }

int32 UVCItemDataAsset::GetMaxItemCount() const { return MaxItemCount; }

void UVCItemDataAsset::SetMaxItemCount(int32 InMaxItemCount) { MaxItemCount = InMaxItemCount < 0 ? 1 : InMaxItemCount; }

const FName& UVCItemDataAsset::GetItemName() const { return ItemName; }

void UVCItemDataAsset::SetItemName(const FName& InName) { ItemName = InName; }

const FText& UVCItemDataAsset::GetItemDescription() const { return ItemDescription; }

void UVCItemDataAsset::SetItemDescription(const FText& InDescription) { ItemDescription = InDescription; }

const FPrimaryAssetType& UVCItemDataAsset::GetItemType() const { return ItemType; }

void UVCItemDataAsset::SetItemType(const FPrimaryAssetType& InType) { ItemType = InType; }

TSubclassOf<AActor> UVCItemDataAsset::GetItemClass() const { return ItemClass; }

void UVCItemDataAsset::SetItemClass(TSubclassOf<AActor> InClass) { ItemClass = InClass; }

UTexture2D* UVCItemDataAsset::GetItemIcon() const { return ItemIcon; }

void UVCItemDataAsset::SetItemIcon(UTexture2D* InIcon) { ItemIcon = InIcon; }
