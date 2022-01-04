// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VCItemDataAsset.h"
#include "VCTypes.h"
#include "Components/ActorComponent.h"
#include "VCInventoryComponent.generated.h"

class UVCItemDataAsset;
class UVCItemSlot;

UCLASS(ClassGroup=(VoxelCraft), meta=(BlueprintSpawnableComponent))
class UEVOXELCRAFT_API UVCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UVCInventoryComponent();

	virtual ~UVCInventoryComponent() override;

protected:
	virtual void BeginPlay() override;

	// FUNCTIONS
protected:
	/** Pass 0 to make the slot empty */
	void DecreaseItemSlotCount(UVCItemSlot* InItemSlot, uint8 InCount = 1);

	/** Pass 0 to make the slot full */
	void IncreaseItemSlotCount(UVCItemSlot* InItemSlot, uint8 InCount = 1);

	/** Forcibly changes an Item in an ItemSlot */
	void InsertInSlot(UVCItemSlot* InItemSlot, UVCItemDataAsset* InItem, uint8 InCount);

	/** Find the first empty slot */
	UVCItemSlot* FindEmptySlot();

	/** Find the first Appropriate slot that can stack this item(AssetID = Name + Type). */
	UVCItemSlot* FindAppropriateSlot(const FPrimaryAssetId& AssetID);

	UVCItemSlot* GetSlot(uint8 InSlotNumber);

	/** number of slots in InventorySlots */
	int32 GetSlotsNum() const;

	bool IsSlotEmpty(const UVCItemSlot* InItemSlot) const;

	bool IsSlotValid(const UVCItemSlot* InItemSlot) const;

	UVCItemDataAsset* GetItem(const UVCItemSlot* InItemSlot);

	void AddItemToInventoryData(UVCItemDataAsset* InOutItemDataAsset, int32 InCount = 1);

	void RemoveItemFromInventoryData(UVCItemDataAsset* InItemDataAsset, int32 InCount = 1);

private:
	/** Used to initialize inventory with the data that designer has entered in InventorySlotsEditor */
	void InventorySlotsInitializer();

	// GETTERS & SETTERS
public:
	// PROPERTIES
protected:
	UPROPERTY(EditAnywhere, Category= "Properties|Inventory")
	TMap<FVCEditorItemSlot, UVCItemDataAsset*> InventorySlotsEditor;

	UPROPERTY()
	TArray<UVCItemDataAsset*> ItemsStrongReferences;

	UPROPERTY()
	TArray<UVCItemSlot*> ItemSlotsStrongReferences;

	UPROPERTY(EditAnywhere, Category= "Properties|Inventory")
	UVCItemSlot* EquippedSlot;

	UPROPERTY(EditAnywhere, Category= "Properties|Inventory")
	TMap<UVCItemDataAsset*, int32 /**count*/> InventoryData;

	TSortedMap<uint8, TPair<UVCItemSlot*, UVCItemDataAsset*>> InventorySlots;
};
