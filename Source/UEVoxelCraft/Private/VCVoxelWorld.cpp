﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "VCVoxelWorld.h"
#include "VCTypes.h"
#include "VCCharacter.h"
#include "VCVoxelChunk.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

AVCVoxelWorld::AVCVoxelWorld() : DrawDistance{5}, VoxelChunkClass{nullptr} { PrimaryActorTick.bCanEverTick = true; }

void AVCVoxelWorld::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	checkf(PlayerPawn.Get(), TEXT("Unable to get player character"));

	if (!VoxelChunkClass)
	{
		UE_LOG(LogTemp, Error, TEXT("VoxelChunkClass not specified in VCVoxelWorld"));
		return;
	}

	const FVector PlayerPosition = GetPlayerPositionInChunkBasis();

	GenerateChunks(PlayerPosition);
}

void AVCVoxelWorld::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CullChunks();

	AddChunks();
}

// FUNCTIONS

void AVCVoxelWorld::GenerateChunks(const FVector& Position)
{
	for (int x = -DrawDistance; x <= DrawDistance; x++)
	{
		for (int y = -DrawDistance; y <= DrawDistance; y++)
		{
			FVector ChunkPosition{FVector{(x + Position.X), (y + Position.Y), 0.0f}};
			if (IsInRadius(ChunkPosition))
			{
				if (!ChunkCoords.Contains(ChunkPosition))
				{
					AVCVoxelChunk* Chunk = Cast<AVCVoxelChunk>(
						GetWorld()->SpawnActor<AActor>(VoxelChunkClass, ChunkPosition * ChunkSize * BlockSize, FRotator::ZeroRotator));
					checkf(Chunk, TEXT("Something went wrong creating chunk %d %d"), x, y);

					Chunks.Add(Chunk);
					ChunkCoords.Add(ChunkPosition);
				}
			}
		}
	}
}

void AVCVoxelWorld::CullChunks()
{
	for (auto It = Chunks.CreateIterator(); It; ++It)
	{
		if (!IsInRadius(*Chunks[It.GetId()]))
		{
			Chunks[It.GetId()]->Destroy();
			Chunks.Remove(Chunks[It.GetId()]);
			ChunkCoords.Remove(ChunkCoords[It.GetId()]);
		}
	}
}

void AVCVoxelWorld::AddChunks()
{
	GenerateChunks(GetPlayerPositionInChunkBasis());
}

FVector AVCVoxelWorld::GetPlayerPositionInChunkBasis() const
{
	const float PositionX = FMath::FloorToInt(PlayerPawn->GetActorLocation().X / (ChunkSize * BlockSize));
	const float PositionY = FMath::FloorToInt(PlayerPawn->GetActorLocation().Y / (ChunkSize * BlockSize));
	return FVector{PositionX, PositionY, 0.0f};
}

bool AVCVoxelWorld::IsInRadius(const FVector& Coords) const
{
	const FVector PlayerPosition = GetPlayerPositionInChunkBasis();

	const FVector BasisVector{static_cast<float>(DrawDistance), static_cast<float>(DrawDistance), 0.0f};

	if ((Coords - PlayerPosition).Size() < BasisVector.Size())
	{
		return true;
	}
	return false;
}

bool AVCVoxelWorld::IsInRadius(const AVCVoxelChunk& Chunk) const
{
	FVector Coords;
	Coords.X = FMath::FloorToInt(Chunk.GetActorLocation().X / (ChunkSize * BlockSize));
	Coords.Y = FMath::FloorToInt(Chunk.GetActorLocation().Y / (ChunkSize * BlockSize));
	Coords.Z = 0.0f;
	return IsInRadius(Coords);
}
