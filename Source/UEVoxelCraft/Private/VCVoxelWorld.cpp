// Fill out your copyright notice in the Description page of Project Settings.


#include "VCVoxelWorld.h"

#include "VCVoxelChunk.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

AVCVoxelWorld::AVCVoxelWorld() : DrawDistance{5}, VoxelChunkClass{nullptr} { PrimaryActorTick.bCanEverTick = false; }

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
			GetWorld()->SpawnActor<AActor>(VoxelChunkClass, FVector(x * ChunkSize * 100, y * ChunkSize * 100, 0),
			                               FRotator::ZeroRotator);
		}
	}
}
