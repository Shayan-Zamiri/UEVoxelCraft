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

	virtual ~UVCItemDataAsset() override = default;

	UFUNCTION(BlueprintCallable)
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	// GETTERS & SETTERS
public:
	UFUNCTION(BlueprintGetter)
	int32 GetItemCount() const;

	UFUNCTION(BlueprintSetter)
	void SetItemCount(int32 InItemCount);

	UFUNCTION(BlueprintGetter)
	int32 GetMaxItemCount() const;

	UFUNCTION(BlueprintSetter)
	void SetMaxItemCount(int32 InMaxItemCount);

	UFUNCTION(BlueprintGetter)
	const FName& GetItemName() const;

	UFUNCTION(BlueprintSetter)
	void SetItemName(const FName& InName);

	UFUNCTION(BlueprintGetter)
	const FText& GetItemDescription() const;

	UFUNCTION(BlueprintSetter)
	void SetItemDescription(const FText& InDescription);

	UFUNCTION(BlueprintGetter)
	const FPrimaryAssetType& GetItemType() const;

	UFUNCTION(BlueprintSetter)
	void SetItemType(const FPrimaryAssetType& InType);

	UFUNCTION(BlueprintGetter)
	TSubclassOf<AActor> GetItemClass() const;

	UFUNCTION(BlueprintSetter)
	void SetItemClass(TSubclassOf<AActor> InClass);

	UFUNCTION(BlueprintGetter)
	UTexture2D* GetItemIcon() const;

	UFUNCTION(BlueprintSetter)
	void SetItemIcon(UTexture2D* InIcon);

	// PROPERTIES
protected:
	/** Number of this item in the whole inventory. */
	UPROPERTY(EditAnywhere, BlueprintGetter= "GetItemCount", BlueprintSetter= "SetItemCount", Category= "Properties")
	int32 ItemCount;

	/** Maximum number of this item that one slot can hold. */
	UPROPERTY(EditAnywhere, BlueprintGetter= "GetMaxItemCount", BlueprintSetter= "SetMaxItemCount", Category= "Properties")
	int32 MaxItemCount;

	UPROPERTY(EditAnywhere, BlueprintGetter= "GetItemName", BlueprintSetter= "SetItemName", Category= "Properties")
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintGetter= "GetItemDescription", BlueprintSetter= "SetItemDescription", Category= "Properties")
	FText ItemDescription;

	/* Examples: Potion, Block, ... (defined in asset manager and project setting) */
	UPROPERTY(EditAnywhere, BlueprintGetter= "GetItemType", BlueprintSetter= "SetItemType", Category= "Properties")
	FPrimaryAssetType ItemType;

	/** Class required to spawn an instance of this item */
	UPROPERTY(EditAnywhere, BlueprintGetter= "GetItemClass", BlueprintSetter= "SetItemClass", Category= "Properties")
	TSubclassOf<AActor> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintGetter= "GetItemIcon", BlueprintSetter= "SetItemIcon", Category= "Properties")
	UTexture2D* ItemIcon;
};
