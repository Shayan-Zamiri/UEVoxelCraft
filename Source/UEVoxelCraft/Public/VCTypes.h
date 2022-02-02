#pragma once
#include "VCAssetManager.h"
#include "VCTypes.generated.h"

// CONSTEXPR

static constexpr int32 ChunkSize = 16;

static constexpr int32 BlockSize = 100;

// ENUMS

UENUM(BlueprintType)
enum class EVCBlockType : uint8
{
	None,
	Stone,
	Dirt
};

UENUM()
enum class EVCDirection : uint8
{
	Forward,
	Right,
	Back,
	Left,
	Up,
	Down
};

inline FName EnumToName(EVCBlockType BlockType)
{
	switch (BlockType)
	{
	case 1: return FName{"Stone"};
	case 2: return FName{"Dirt"};
	default: return FName{"None"};
	}
}

UENUM()
enum class VCNoiseType : uint8
{
	NoiseType_OpenSimplex2,
	NoiseType_OpenSimplex2S,
	NoiseType_Cellular,
	NoiseType_Perlin,
	NoiseType_ValueCubic,
	NoiseType_Value
};

UENUM()
enum class VCRotationType3D : uint8
{
	RotationType3D_None,
	RotationType3D_ImproveXYPlanes,
	RotationType3D_ImproveXZPlanes
};

UENUM()
enum class VCFractalType : uint8
{
	FractalType_None,
	FractalType_FBm,
	FractalType_Ridged,
	FractalType_PingPong,
	FractalType_DomainWarpProgressive,
	FractalType_DomainWarpIndependent
};

// STRUCTS

USTRUCT(BlueprintType)
struct FVCChunkMeshData
{
	GENERATED_BODY()

	~FVCChunkMeshData()
	{
		Vertices.Empty();
		Indices.Empty();
		Normals.Empty();
		UV.Empty();
	}

	void Clear()
	{
		Vertices.Empty();
		Indices.Empty();
		Normals.Empty();
		UV.Empty();
		VertexCount = 0;
	}

	TArray<FVector> Vertices;
	TArray<int32> Indices;
	TArray<FVector> Normals;
	TArray<FVector2D> UV;

	int32 VertexCount;
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

// DELEGATES

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnTakeDamageSignature, class UVCHealthComponent* HealthComponent, float CurrentHealth,
                                       AController* InstigatedBy);
