// Fill out your copyright notice in the Description page of Project Settings.


#include "VCVoxelWorld.h"
#include "VCTypes.h"
#include "VCCharacter.h"
#include "VCVoxelChunk.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

AVCVoxelWorld::AVCVoxelWorld() : DrawDistance{5}, VoxelChunkClass{nullptr} { PrimaryActorTick.bCanEverTick = true; }

void AVCVoxelWorld::BeginPlay()
{
	Super::BeginPlay();

	if (!VoxelChunkClass)
	{
		UE_LOG(LogTemp, Error, TEXT("VoxelChunkClass not specified in VCVoxelWorld"));
		return;
	}

	for (int x = -DrawDistance; x <= DrawDistance; x++)
	{
		for (int y = -DrawDistance; y <= DrawDistance; y++)
		{
			AVCVoxelChunk* Chunk = Cast<AVCVoxelChunk>(GetWorld()->SpawnActor<AActor>(
				VoxelChunkClass, FVector(x * ChunkSize * BlockSize, y * ChunkSize * BlockSize, 0), FRotator::ZeroRotator));
			checkf(Chunk, TEXT("Something went wrong creating chunk %d %d"), x, y);

			Chunks.Add(Chunk);
		}
	}
}

void AVCVoxelWorld::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CullChunks();
}

// FUNCTIONS

void AVCVoxelWorld::CullChunks()
{
	for (int Index = 0; Index < Chunks.Num(); ++Index)
	{
		if (!IsInRadius(*Chunks[Index]))
		{
			Chunks[Index]->Destroy();
			Chunks.RemoveAt(Index);
		}
	}
}

bool AVCVoxelWorld::IsInRadius(const FVector& InCoords) const
{
	AVCCharacter* PlayerCharacter = Cast<AVCCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	checkf(PlayerCharacter, TEXT("Unable to get player character"));

	const float PositionX = FMath::FloorToInt(PlayerCharacter->GetActorLocation().X / (ChunkSize * BlockSize));
	const float PositionY = FMath::FloorToInt(PlayerCharacter->GetActorLocation().Y / (ChunkSize * BlockSize));
	const FVector PlayerPosition{PositionX, PositionY, 0.0f};

	const FVector BasisVector{static_cast<float>(DrawDistance), static_cast<float>(DrawDistance), 0.0f};

	if ((InCoords - PlayerPosition).Size() < BasisVector.Size()) { return true; }
	return false;
}

bool AVCVoxelWorld::IsInRadius(const AVCVoxelChunk& InChunk) const
{
	FVector Coords;
	Coords.X = FMath::FloorToInt(InChunk.GetActorLocation().X / (ChunkSize * BlockSize));
	Coords.Y = FMath::FloorToInt(InChunk.GetActorLocation().Y / (ChunkSize * BlockSize));
	Coords.Z = 0.0f;
	return IsInRadius(Coords);
}

