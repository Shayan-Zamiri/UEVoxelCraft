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

	static FVector GetPositionInDirection(const FVector& InPosition, const EVCDirection InDirection);

	static FIntVector WorldLocationToBlockPosition(const FVector& InWorldLocation);

	static FIntVector WorldLocationToBlockLocalPosition(const FVector& InWorldLocation);

	static FIntVector WorldLocationToChunkPosition(const FVector& InWorldLocation);

	void RuntimeMeshSetup();

	void NoiseSetup();

	void SetupBlockVariety();

	void GenerateChunk();

	void GenerateMesh();

	void ApplyMesh();

	void ClearMesh();

	void CreateFace(const FVector& InPosition, EVCDirection InDirection, const EVCBlockType InBlock);

	void AddVertices(const FVector& InPosition, EVCDirection InDirection, const EVCBlockType InBlock);

	void AddIndices(const EVCBlockType InBlock);

	void AddUVs(const EVCBlockType InBlock);

	/** Checks whether or not the block in the specified position is of type EVCBlockType::None */
	bool CheckNone(const FVector& InPosition);

	UMaterialInterface* GetMaterialInterfaceFromBlock(const EVCBlockType InBlock) const;

	void ModifyChunkMesh(const FIntVector& InPosition, const EVCBlockType InBlock);

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

	UPROPERTY()
	URuntimeMeshComponent* RMComp;

	UPROPERTY()
	URuntimeMeshProviderStatic* RMProviderStatic;

private:
	TMap<EVCBlockType, FVCChunkMeshData> MeshData;

	FastNoiseLite* Noise;
};
