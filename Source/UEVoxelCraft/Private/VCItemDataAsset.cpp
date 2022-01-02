// Fill out your copyright notice in the Description page of Project Settings.


#include "VCItemDataAsset.h"
#include "VCAssetManager.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

UVCItemDataAsset::UVCItemDataAsset() : ItemType{UVCAssetManager::InventoryItem}, ItemClass{nullptr}, ItemIcon{nullptr} {}

UVCItemDataAsset::UVCItemDataAsset(const FText& InItemName, const FText& InItemDescription, const FPrimaryAssetType& InItemType,
                                   const TSoftClassPtr<AActor>& InItemClass, const TSoftObjectPtr<UTexture2D>& InItemIcon)
	: ItemName{InItemName}, ItemDescription{InItemDescription}, ItemType{InItemType}, ItemClass{InItemClass}, ItemIcon{InItemIcon} {}

FPrimaryAssetId UVCItemDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(ItemType, GetFName());
}

// GETTERS & SETTERS

const FText& UVCItemDataAsset::GetItemName() const
{
	return ItemName;
}

void UVCItemDataAsset::SetItemName(const FText& InName)
{
	ItemName = InName;
}

const FText& UVCItemDataAsset::GetItemDescription() const
{
	return ItemDescription;
}

void UVCItemDataAsset::SetItemDescription(const FText& InDescription)
{
	ItemDescription = InDescription;
}

const FPrimaryAssetType& UVCItemDataAsset::GetItemType() const
{
	return ItemType;
}

void UVCItemDataAsset::SetItemType(const FPrimaryAssetType& InType)
{
	ItemType = InType;
}

const TSoftClassPtr<AActor>& UVCItemDataAsset::GetItemClass() const
{
	return ItemClass;
}

void UVCItemDataAsset::SetItemClass(const TSoftClassPtr<AActor>& InClass)
{
	ItemClass = InClass;
}

const TSoftObjectPtr<UTexture2D>& UVCItemDataAsset::GetItemIcon() const
{
	return ItemIcon;
}

void UVCItemDataAsset::SetItemIcon(const TSoftObjectPtr<UTexture2D>& InIcon)
{
	ItemIcon = InIcon;
}
