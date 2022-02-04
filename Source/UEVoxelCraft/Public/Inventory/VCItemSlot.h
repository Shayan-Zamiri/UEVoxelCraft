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

	virtual ~UVCItemSlot() override = default;

	// FUNCTIONS
public:
	bool operator<(const UVCItemSlot& rhs) const { return SlotNumber < rhs.SlotNumber; }

	UFUNCTION(BlueprintCallable, Category= "Functions")
	bool IsSlotValid() const;

	UFUNCTION(BlueprintCallable, Category= "Functions")
	bool IsSlotEmpty() const;

	/** If you want to fill the slot by the item that is currently held in the slot, pass nothing*/
	int32 GetSlotMaxCount() const;

	void EmptySlot();

	/** If you want to fill the slot by the item that is currently held in the slot, pass nothing*/
	void FillSlot(const UVCItemDataAsset* InItemDA = nullptr);

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

	UFUNCTION(BlueprintGetter)
	const UVCItemDataAsset* GetItem() const;

	UFUNCTION(BlueprintSetter)
	void SetItem(const UVCItemDataAsset* InItemDA);

	// PROPERTIES
protected:
	UPROPERTY(EditAnywhere, BlueprintGetter= "GetSlotNumber", BlueprintSetter= "SetSlotNumber", Category= "Properties|ItemSlot")
	int32 SlotNumber;

	/** Number of item than is held in the slot */
	UPROPERTY(EditAnywhere, BlueprintGetter= "GetSlotItemCount", BlueprintSetter= "SetSlotItemCount", Category= "Properties|ItemSlot")
	int32 SlotItemCount;

	/** Item type than can be held in the slot */
	UPROPERTY(EditAnywhere, BlueprintGetter= "GetSlotItemType", BlueprintSetter= "SetSlotItemType", Category= "Properties|ItemSlot")
	FPrimaryAssetType SlotItemType;

	/** Pointer to item that is held in the slot */
	UPROPERTY(VisibleAnywhere, Instanced, BlueprintGetter= "GetItem", BlueprintSetter= "SetItem", Category= "Properties|ItemSlot")
	const UVCItemDataAsset* Item;
};
