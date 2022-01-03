// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
public:
	// Leave InCount to 1 for a decrement. Pass 0 to make the slot empty
	void DecreaseItemSlotCount(UVCItemSlot* InItemSlot, uint8 InCount = 1);
	
	// GETTERS & SETTERS
public:

	// PROPERTIES
private:
	UPROPERTY(EditAnywhere, Category= "Properties|Inventory")
	TMap<FVCEditorItemSlot, UVCItemDataAsset*> InventorySlotsEditor;

	UPROPERTY()
	TArray<UVCItemDataAsset*> ItemsStrongReferences;

	UPROPERTY()
	TArray<UVCItemSlot*> ItemSlotsStrongReferences;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Properties|Inventory")
	UVCItemSlot* EquippedSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Properties|Inventory")
	TMap<UVCItemDataAsset*, uint8 /**count*/> InventoryData;

	TSortedMap<uint8, TPair<UVCItemSlot*, UVCItemDataAsset*>> InventorySlots;
};
