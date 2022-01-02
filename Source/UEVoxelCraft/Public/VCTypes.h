#pragma once
#include "VCAssetManager.h"
#include "VCTypes.generated.h"

UENUM(BlueprintType)
enum class EVCBiomeType : uint8
{
	Desert,
	Forest,
	Ocean,
	Plain
	//...
};

USTRUCT(BlueprintType)
struct UEVOXELCRAFT_API FVCBiomes
{
	GENERATED_BODY()

	EVCBiomeType BiomeType;
	int8 Temperature;
	uint8 Rainfall; // 0 - 100
};

USTRUCT(BlueprintType)
struct UEVOXELCRAFT_API FVCEditorItemSlot
{
	GENERATED_BODY()

	FVCEditorItemSlot() : SlotNumber{0}, SlotMaxCount{0}, SlotItemCount{0}, SlotItemType(UVCAssetManager::InventoryItem)
	{
	}

	UPROPERTY(EditAnywhere, Category= "Properties")
	uint8 SlotNumber;

	UPROPERTY(EditAnywhere, Category= "Properties")
	uint8 SlotMaxCount;

	UPROPERTY(EditAnywhere, Category= "Properties")
	uint8 SlotItemCount;

	UPROPERTY(EditAnywhere, Category= "Properties")
	FPrimaryAssetType SlotItemType;


	friend uint32 GetTypeHash(const FVCEditorItemSlot& key)
	{
		uint32 Hash = 0;
		Hash = HashCombine(Hash, key.SlotNumber);
		Hash = HashCombine(Hash, GetTypeHash(key.SlotItemType));
		return Hash;
	}
};
