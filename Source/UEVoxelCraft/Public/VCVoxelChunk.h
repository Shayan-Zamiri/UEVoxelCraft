// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VCTypes.h"
#include "VCVoxelChunk.generated.h"

class URuntimeMeshComponent;
class URuntimeMeshProvider;
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
	static int32 GetBlockIndex(int32 X, int32 Y, int32 Z);

	static FVector GetPositionInDirection(FVector InPosition, EVCDirection InDirection);

	static FIntVector WorldLocationToBlockPosition(const FVector& WorldLocation);

	static FIntVector WorldLocationToBlockLocalPosition(const FVector& WorldLocation);

	static FIntVector WorldLocationToChunkPosition(const FVector& WorldLocation);

	void NoiseSetup();

	void SetupBlockVariety();

	void GenerateChunk();

	void GenerateMesh();

	void ApplyMesh();

	void ClearMesh();

	void CreateFace(FVector Position, EVCDirection Direction, EVCBlockType Block);

	void AddVertices(FVector Position, EVCDirection Direction, EVCBlockType Block);

	void AddIndices(EVCBlockType Block);

	void AddUVs(EVCBlockType Block);

	bool CheckNone(FVector Position);

	UMaterialInterface* GetMaterialInterfaceFromBlock(EVCBlockType Block) const;

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
	VCNoiseType NoiseType;

	UPROPERTY(EditAnywhere, Category="Properties")
	VCFractalType FractalType;

	UPROPERTY(VisibleInstanceOnly, Category= "Properties")
	TArray<EVCBlockType> Blocks;

	UPROPERTY(VisibleInstanceOnly, Category= "Properties")
	TSet<EVCBlockType> BlockVariety;

	UPROPERTY(VisibleInstanceOnly, Category= "Properties")
	TMap<EVCBlockType, uint32> VertexCounts;

	UPROPERTY()
	URuntimeMeshComponent* RMComp;

private:
	TMap<EVCBlockType, FVCChunkMeshData> MeshData;

	FastNoiseLite* Noise;
};
