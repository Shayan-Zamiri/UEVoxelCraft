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
