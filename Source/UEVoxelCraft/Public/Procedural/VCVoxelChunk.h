// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VCTypes.h"
#include "VCVoxelChunk.generated.h"

class URuntimeMeshComponent;
class URuntimeMeshProviderStatic;
class FastNoiseLite;

UCLASS()
class UEVOXELCRAFT_API AVCVoxelChunk : public AActor
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AVCVoxelChunk();

	virtual ~AVCVoxelChunk() override;

protected:
	virtual void BeginPlay() override;

	// FUNCTIONS
public:
	static int32 GetBlockIndex(const int32 X, const int32 Y, const int32 Z);

	static FVector GetPositionInDirection(const FVector& Position, const EVCDirection Direction);

	static FIntVector WorldLocationToBlockPosition(const FVector& WorldLocation);

	static FIntVector WorldLocationToBlockLocalPosition(const FVector& WorldLocation);

	static FIntVector WorldLocationToChunkPosition(const FVector& WorldLocation);

	void RuntimeMeshSetup();

	void NoiseSetup();

	void SetupBlockVariety();

	void GenerateChunk();

	void GenerateMesh();

	void ApplyMesh();

	void ClearMesh();

	void CreateFace(const FVector& Position, const EVCDirection Direction, const EVCBlockType Block);

	void AddVertices(const FVector& Position, const EVCDirection Direction, const EVCBlockType Block);

	void AddIndices(const EVCBlockType Block);

	void AddUVs(const EVCBlockType Block);

	/** Checks whether or not the block in the specified position is of type EVCBlockType::None */
	bool CheckNone(const FVector& Position);

	UMaterialInterface* GetMaterialInterfaceFromBlock(const EVCBlockType Block) const;

	void ModifyChunkMesh(const FIntVector& Position, const EVCBlockType Block);

	// GETTERS & SETTERS
public:
	// PROPERTIES
public:
	static const TArray<FVector> BlockVerticesData;

	static const TArray<int32> BlockIndicesData;

protected:
	UPROPERTY(EditAnywhere, Category="Properties")
	float Frequency;

	UPROPERTY(EditAnywhere, Category="Properties")
	float Amplitude;

	UPROPERTY(EditAnywhere, Category="Properties")
	VCNoiseType NoiseType;

	UPROPERTY(EditAnywhere, Category="Properties")
	VCFractalType FractalType;

	UPROPERTY(VisibleInstanceOnly, Category= "Properties")
	TArray<EVCBlockType> Blocks;

	UPROPERTY(VisibleInstanceOnly, Category= "Properties")
	TSet<EVCBlockType> BlockVariety;

	UPROPERTY()
	URuntimeMeshComponent* RMComp;

	UPROPERTY()
	URuntimeMeshProviderStatic* RMProviderStatic;

private:
	TMap<EVCBlockType, FVCChunkMeshData> MeshData;

	FastNoiseLite* Noise;
};
