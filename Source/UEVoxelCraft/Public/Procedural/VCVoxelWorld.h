// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VCVoxelWorld.generated.h"

class AVCVoxelChunk;
class AVCCharacter;

UCLASS()
class UEVOXELCRAFT_API AVCVoxelWorld : public AActor
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AVCVoxelWorld();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	// FUNCTIONS
private:
	/** Spawns chunks around the specified position */
	void GenerateChunks(const FVector& Position);

	void CullChunks();

	void AddChunks();

	/** Calculates player position in a chunk scale */
	FVector GetPlayerPositionInChunkBasis() const;

	bool IsInRadius(const FVector& Coords) const;

	bool IsInRadius(const AVCVoxelChunk& Chunk) const;

	// PROPERTIES
protected:
	UPROPERTY(EditAnywhere, Category= "Properties")
	int32 DrawDistance;

	UPROPERTY(EditAnywhere, Category= "Properties")
	TSubclassOf<AVCVoxelChunk> VoxelChunkClass;

	TSet<AVCVoxelChunk*> Chunks;

	TSet<FVector> ChunkCoords;

	TWeakObjectPtr<APawn> PlayerPawn;
};
