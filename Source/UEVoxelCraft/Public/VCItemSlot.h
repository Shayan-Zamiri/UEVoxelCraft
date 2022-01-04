// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VCItemSlot.Generated.h"

class UVCItemDataAsset;

UCLASS()
class UEVOXELCRAFT_API UVCItemSlot : public UObject
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UVCItemSlot();

	UVCItemSlot(const FPrimaryAssetType InSlotItemType, const uint8 InSlotNumber);

	UVCItemSlot(const uint8 InSlotNumber, const uint8 InSlotMaxCount, const FPrimaryAssetType& InItemType);

	virtual ~UVCItemSlot() override = default;

	// FUNCTIONS
public:
	UFUNCTION(BlueprintCallable, Category= "Functions")
	bool IsSlotValid() const;

	UFUNCTION(BlueprintCallable, Category= "Functions")
	bool IsSlotEmpty() const;

	/* Defined so that our ItemSlots can be sorted by TSortedMap<> */
	bool operator<(const UVCItemSlot& rhs) const { return SlotNumber < rhs.SlotNumber; }
	
	int32 GetSlotMaxCount() const;


	// GETTERS & SETTERS
public:
	UFUNCTION(BlueprintGetter)
	int32 GetSlotNumber() const;

	UFUNCTION(BlueprintSetter)
	void SetSlotNumber(int32 InSlotNum);

	UFUNCTION(BlueprintGetter)
	int32 GetSlotItemCount() const;

	UFUNCTION(BlueprintSetter)
	void SetSlotItemCount(int32 InSlotItemCount);

	UFUNCTION(BlueprintGetter)
	const FPrimaryAssetType& GetSlotItemType() const;

	UFUNCTION(BlueprintSetter)
	void SetSlotItemType(const FPrimaryAssetType& InSlotItemType);
	
	const TWeakObjectPtr<UVCItemDataAsset>& GetItemReference() const; 	
	
	void SetItemReference(UVCItemDataAsset* InOutItemDataAsset);
	
	// PROPERTIES
protected:
	UPROPERTY(EditAnywhere, BlueprintGetter= "GetSlotNumber", BlueprintSetter= "SetSlotNumber", Category= "Properties|ItemSlot")
	int32 SlotNumber;

	UPROPERTY(EditAnywhere, BlueprintGetter= "GetSlotItemCount", BlueprintSetter= "SetSlotItemCount", Category= "Properties|ItemSlot")
	int32 SlotItemCount;

	UPROPERTY(EditAnywhere, BlueprintGetter= "GetSlotItemType", BlueprintSetter= "SetSlotItemType", Category= "Properties|ItemSlot")
	FPrimaryAssetType SlotItemType;

	UPROPERTY()
	TWeakObjectPtr<UVCItemDataAsset> ItemReference;
};
