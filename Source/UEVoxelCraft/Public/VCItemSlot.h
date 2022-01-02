// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VCItemSlot.Generated.h"

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

	// GETTERS & SETTERS
public:
	UFUNCTION(BlueprintGetter)
	uint8 GetSlotNumber() const;

	UFUNCTION(BlueprintSetter)
	void SetSlotNumber(uint8 InSlotNum);

	UFUNCTION(BlueprintGetter)
	uint8 GetSlotMaxCount() const;

	UFUNCTION(BlueprintSetter)
	void SetSlotMaxCount(uint8 InSlotMaxCount);

	UFUNCTION(BlueprintGetter)
	uint8 GetSlotItemCount() const;

	UFUNCTION(BlueprintSetter)
	void SetSlotItemCount(uint8 InSlotItemCount);

	UFUNCTION(BlueprintGetter)
	const FPrimaryAssetType& GetSlotItemType() const;

	UFUNCTION(BlueprintSetter)
	void SetSlotItemType(const FPrimaryAssetType& InSlotItemType);

	// PROPERTIES
protected:
	UPROPERTY(EditAnywhere, BlueprintGetter= "GetSlotNumber", BlueprintSetter= "SetSlotNumber", Category= "Properties|ItemSlot")
	uint8 SlotNumber;

	UPROPERTY(EditAnywhere, BlueprintGetter= "GetSlotMaxCount", BlueprintSetter= "SetSlotMaxCount", Category= "Properties|ItemSlot")
	uint8 SlotMaxCount;

	UPROPERTY(EditAnywhere, BlueprintGetter= "GetSlotItemCount", BlueprintSetter= "SetSlotItemCount", Category= "Properties|ItemSlot")
	uint8 SlotItemCount;

	UPROPERTY(EditAnywhere, BlueprintGetter= "GetSlotItemType", BlueprintSetter= "SetSlotItemType", Category= "Properties|ItemSlot")
	FPrimaryAssetType SlotItemType;
};
