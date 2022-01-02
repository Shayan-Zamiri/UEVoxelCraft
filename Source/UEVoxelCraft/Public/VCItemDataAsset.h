﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "VCItemDataAsset.generated.h"

UCLASS()
class UEVOXELCRAFT_API UVCItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UVCItemDataAsset();
	UVCItemDataAsset(const FText& InItemName, const FText& ItemDescription, const FPrimaryAssetType& InItemType,
	                 const TSoftClassPtr<AActor>& InItemClass, const TSoftObjectPtr<UTexture2D>& InItemIcon);

	virtual ~UVCItemDataAsset() override = default;

	UFUNCTION()
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	// GETTERS & SETTERS
public:
	UFUNCTION(BlueprintGetter)
	const FText& GetItemName() const;

	UFUNCTION(BlueprintSetter)
	void SetItemName(const FText& InName);

	UFUNCTION(BlueprintGetter)
	const FText& GetItemDescription() const;

	UFUNCTION(BlueprintSetter)
	void SetItemDescription(const FText& InDescription);

	UFUNCTION(BlueprintGetter)
	const FPrimaryAssetType& GetItemType() const;

	UFUNCTION(BlueprintSetter)
	void SetItemType(const FPrimaryAssetType& InType);

	UFUNCTION(BlueprintGetter)
	const TSoftClassPtr<AActor>& GetItemClass() const;

	UFUNCTION(BlueprintSetter)
	void SetItemClass(const TSoftClassPtr<AActor>& InClass);

	UFUNCTION(BlueprintGetter)
	const TSoftObjectPtr<UTexture2D>& GetItemIcon() const;

	UFUNCTION(BlueprintSetter)
	void SetItemIcon(const TSoftObjectPtr<UTexture2D>& InIcon);

	// PROPERTIES
protected:
	UPROPERTY(EditAnywhere, BlueprintGetter= "GetItemName", BlueprintSetter= "SetItemName", Category= "Properties")
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintGetter= "GetItemDescription", BlueprintSetter= "SetItemDescription", Category= "Properties")
	FText ItemDescription;

	/* Examples: Potion, Block, ... (defined in assset manager and project setting) */
	UPROPERTY(EditAnywhere, BlueprintGetter= "GetItemType", BlueprintSetter= "SetItemType", Category= "Properties")
	FPrimaryAssetType ItemType;

	/** Class required to spawn an instance of this item */
	UPROPERTY(EditAnywhere, BlueprintGetter= "GetItemClass", BlueprintSetter= "SetItemClass", Category= "Properties", meta=(AssetBundles= Inventory))
	TSoftClassPtr<AActor> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintGetter= "GetItemIcon", BlueprintSetter= "SetItemIcon", Category= "Properties", meta=(AssetBundles= Inventory))
	TSoftObjectPtr<UTexture2D> ItemIcon;
};