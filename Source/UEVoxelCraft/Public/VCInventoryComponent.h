// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VCTypes.h"
#include "Components/ActorComponent.h"
#include "VCInventoryComponent.generated.h"

class UVCItemDataAsset;
class UVCItemSlot;
class UVCInventoryUI;

UCLASS(ClassGroup=(VoxelCraft), meta=(BlueprintSpawnableComponent), Blueprintable)
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
public:
	/** number of slots in InventorySlots */
	int32 GetSlotsNum() const;

	const UVCItemDataAsset* GetItem(int32 SlotNumber);

	void AddItem(const FPrimaryAssetId& InItemID, int32 Count = 1);

	bool ContainsItem(const FPrimaryAssetId& InItemID) const;

	void UpdateInventoryUI();

	void UpdateInventoryUIAt(const int Index);

	void ShowInventory();
	
	void HideInventory();

protected:
	/** Pass 0 to make the slot empty */
	void DecreaseItemSlotCount(int32 SlotNumber, int32 Count = 1);

	/** Pass 0 to make the slot full */
	void IncreaseItemSlotCount(int32 SlotNumber, int32 Count = 1);

	/** Forcibly changes an Item in an ItemSlot */
	void InsertInSlot(int32 SlotNumber, int32 Count, UVCItemDataAsset* InItem);

	/** Find the first empty slot, returns nullptr if it can't find anything */
	UVCItemSlot* FindEmptySlot();

	/** Find the first Appropriate slot that can stack this item(AssetID = Name + Type), returns nullptr if it can't find anything. */
	UVCItemSlot* FindAppropriateSlot(const FPrimaryAssetId& AssetID);

	UVCItemSlot& GetSlot(int32 SlotNumber);

	bool IsSlotValid(const UVCItemSlot* InItemSlot) const;

	bool IsSlotEmpty(int32 SlotNumber);

	void AddItemToInventoryData(const FPrimaryAssetId& InItemID, UVCItemDataAsset* InOutItemDA);

	void RemoveItemFromInventoryData(const FPrimaryAssetId& InItemID, int32 Count = 1);

	void LoadAndAddItem(const FPrimaryAssetId& InItemID, int32 SlotNumber, int32 Count = 1);

	UFUNCTION()
	void OnLoadItem(FPrimaryAssetId ItemID, int32 SlotNumber, int32 Count);

	void SetupUI();

private:
	/** Always ensure that we have made slots in the amount of SlotCount in the constructor */
	void InventorySlotsInitializer();

	// GETTERS & SETTERS
public:
	// PROPERTIES
protected:
	UPROPERTY(VisibleAnywhere, Category= "Properties")
	int32 SlotCount;

	UPROPERTY(EditAnywhere, Category= "Properties")
	UVCItemSlot* EquippedSlot;

	UPROPERTY(EditAnywhere, Category= "Properties")
	TSubclassOf<UVCInventoryUI> InventoryUIClass;

	UPROPERTY(VisibleAnywhere, Category= "Properties")
	UVCInventoryUI* InventoryUI;

	UPROPERTY(VisibleAnywhere, Instanced, Category= "Properties")
	TMap<FPrimaryAssetId, UVCItemDataAsset*> InventoryData;

	UPROPERTY(VisibleAnywhere, Instanced, Category= "Properties")
	TArray<UVCItemSlot*> InventorySlots;
};
