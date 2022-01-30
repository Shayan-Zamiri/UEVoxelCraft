﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "VCVoxelChunk.h"
#include "RuntimeMeshComponent.h"
#include "VCGameInstance.h"
#include "Providers/RuntimeMeshProviderStatic.h"
#include "FastNoiseLite.h"

// STATICS

const TArray<FVector> AVCVoxelChunk::BlockVerticesData
{
	{
		FVector(BlockSize, BlockSize, BlockSize),
		FVector(BlockSize, 0, BlockSize),
		FVector(BlockSize, 0, 0),
		FVector(BlockSize, BlockSize, 0),
		FVector(0, 0, BlockSize),
		FVector(0, BlockSize, BlockSize),
		FVector(0, BlockSize, 0),
		FVector(0, 0, 0)
	}
};

const TArray<int32> AVCVoxelChunk::BlockIndicesData
{
	{
		0, 1, 2, 3, // Forward
		5, 0, 3, 6, // Right
		4, 5, 6, 7, // Back
		1, 4, 7, 2, // Left
		5, 4, 1, 0, // Up
		3, 2, 7, 6 // Down
	}
};

int32 AVCVoxelChunk::GetBlockIndex(int32 X, int32 Y, int32 Z) { return X * ChunkSize * ChunkSize + Y * ChunkSize + Z; }

FVector AVCVoxelChunk::GetPositionInDirection(FVector InPosition, EVCDirection InDirection)
{
	switch (InDirection)
	{
	case EVCDirection::Forward:
		return InPosition + FVector::ForwardVector;
	case EVCDirection::Right:
		return InPosition + FVector::RightVector;
	case EVCDirection::Back:
		return InPosition + FVector::BackwardVector;
	case EVCDirection::Left:
		return InPosition + FVector::LeftVector;
	case EVCDirection::Up:
		return InPosition + FVector::UpVector;
	case EVCDirection::Down:
		return InPosition + FVector::DownVector;
	default:
		UE_LOG(LogTemp, Fatal, TEXT("Invalid Direction")); // crashes the session
		return FVector{}; // written to ignore IDE warning
	}
}

FIntVector AVCVoxelChunk::WorldLocationToBlockPosition(const FVector& WorldLocation)
{
	FIntVector Position{};
	Position.X = FMath::FloorToInt(WorldLocation.X / BlockSize);
	Position.Y = FMath::FloorToInt(WorldLocation.Y / BlockSize);
	Position.Z = FMath::FloorToInt(WorldLocation.Z / BlockSize);
	return Position;
}

FIntVector AVCVoxelChunk::WorldLocationToBlockLocalPosition(const FVector& WorldLocation)
{
	const FIntVector ChunkPosition = WorldLocationToChunkPosition(WorldLocation);
	const FIntVector BlockPosition = WorldLocationToBlockPosition(WorldLocation);
	return BlockPosition - ChunkPosition * ChunkSize;
}

FIntVector AVCVoxelChunk::WorldLocationToChunkPosition(const FVector& WorldLocation)
{
	FIntVector Position{};
	Position.X = FMath::FloorToInt(WorldLocation.X / (ChunkSize * BlockSize));
	Position.Y = FMath::FloorToInt(WorldLocation.Y / (ChunkSize * BlockSize));
	Position.Z = FMath::FloorToInt(WorldLocation.Z / (ChunkSize * BlockSize));
	return Position;
}

// CTOR/DTOR & VIRTUAL FUNCTIONS

AVCVoxelChunk::AVCVoxelChunk() : Frequency{0.05f}, NoiseType{VCNoiseType::NoiseType_Perlin},
                                 FractalType{VCFractalType::FractalType_FBm}
{
	PrimaryActorTick.bCanEverTick = false;

	RMComp = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("RuntimeMeshComp"));
	RMComp->SetMobility(EComponentMobility::Static);
	RootComponent = RMComp;

	Noise = new FastNoiseLite();
	Blocks.SetNum(ChunkSize * ChunkSize * ChunkSize);
}

AVCVoxelChunk::~AVCVoxelChunk() { delete Noise; }

void AVCVoxelChunk::BeginPlay()
{
	Super::BeginPlay();

	NoiseSetup();

	SetupBlockVariety();

	GenerateChunk();

	GenerateMesh();

	ApplyMesh();
}

// FUNCTIONS

void AVCVoxelChunk::NoiseSetup()
{
	Noise->SetFrequency(Frequency);
	Noise->SetNoiseType(static_cast<FastNoiseLite::NoiseType>(NoiseType));
	Noise->SetFractalType(static_cast<FastNoiseLite::FractalType>(FractalType));
}

void AVCVoxelChunk::SetupBlockVariety()
{
	UVCGameInstance* GameInstance = Cast<UVCGameInstance>(GetGameInstance());
	if (!GameInstance)
		return;

	for (const auto& It : GameInstance->Materials)
	{
		BlockVariety.Add(It.Key);
		VertexCounts.Add(It.Key);
		MeshData.Add(It.Key);
	}
}

void AVCVoxelChunk::GenerateChunk()
{
	const FVector Location = GetActorLocation();

	for (int32 x = 0; x < ChunkSize; x++)
	{
		for (int32 y = 0; y < ChunkSize; y++)
		{
			const float XPos = x + Location.X / BlockSize;
			const float YPos = y + Location.Y / BlockSize;

			const int Height = FMath::Clamp(FMath::RoundToInt((Noise->GetNoise(XPos, YPos) + 1) / 2 * ChunkSize), 1, ChunkSize);

			for (int32 z = 0; z < Height / 2; z++) { Blocks[GetBlockIndex(x, y, z)] = EVCBlockType::Dirt; }

			for (int32 z = Height / 2; z < Height; z++) { Blocks[GetBlockIndex(x, y, z)] = EVCBlockType::Stone; }

			for (int32 z = Height; z < ChunkSize; z++) { Blocks[GetBlockIndex(x, y, z)] = EVCBlockType::None; }
		}
	}
}

void AVCVoxelChunk::GenerateMesh()
{
	for (int32 x = 0; x < ChunkSize; x++)
	{
		for (int32 y = 0; y < ChunkSize; y++)
		{
			for (int32 z = 0; z < ChunkSize; z++)
			{
				const EVCBlockType Block = Blocks[GetBlockIndex(x, y, z)];
				if (Block != EVCBlockType::None)
				{
					const FVector Position = FVector(x, y, z);

					for (const auto Direction : {
						     EVCDirection::Forward, EVCDirection::Right, EVCDirection::Back, EVCDirection::Left, EVCDirection::Up,
						     EVCDirection::Down
					     })
					{
						if (CheckNone(GetPositionInDirection(Position, Direction)))
						{
							CreateFace(Position * BlockSize, Direction, Block);
						}
					}
				}
			}
		}
	}
}

void AVCVoxelChunk::ApplyMesh()
{
	URuntimeMeshProviderStatic* RMProviderStatic = NewObject<URuntimeMeshProviderStatic>(
		this,TEXT("RunetimeMeshProviderStatic"));
	if (RMProviderStatic)
	{
		RMComp->Initialize(RMProviderStatic);
		for (auto It : BlockVariety)
		{
			const uint8 Block = static_cast<uint8>(It);
			RMProviderStatic->SetupMaterialSlot(Block, EnumToName(It), GetMaterialInterfaceFromBlock(It));
			RMProviderStatic->CreateSectionFromComponents(0,
			                                              Block,
			                                              Block,
			                                              MeshData.FindChecked(It).Vertices,
			                                              MeshData.FindChecked(It).Indices,
			                                              TArray<FVector>{},
			                                              MeshData.FindChecked(It).UV,
			                                              TArray<FColor>{},
			                                              TArray<FRuntimeMeshTangent>{},
			                                              ERuntimeMeshUpdateFrequency::Infrequent,
			                                              true);
		}
	}
}

void AVCVoxelChunk::ClearMesh()
{
	for (const auto It : BlockVariety)
	{
		MeshData.FindChecked(It).Clear();
		VertexCounts.FindChecked(It) = 0;
	}
}

void AVCVoxelChunk::CreateFace(FVector Position, EVCDirection Direction, EVCBlockType Block)
{
	AddIndices(Block);
	AddVertices(Position, Direction, Block);
	AddUVs(Block);
}

void AVCVoxelChunk::AddVertices(FVector Position, EVCDirection Direction, EVCBlockType Block)
{
	for (int32 i = 0; i < 4; i++)
	{
		MeshData.FindChecked(Block).Vertices.
		         Add(BlockVerticesData[BlockIndicesData[i + 4 * static_cast<int32>(Direction)]] + Position);
		VertexCounts.FindChecked(Block)++;
	}
}

void AVCVoxelChunk::AddUVs(EVCBlockType Block)
{
	MeshData.FindChecked(Block).UV.Add(FVector2D{0.0f, 0.0f});
	MeshData.FindChecked(Block).UV.Add(FVector2D{1.0f, 0.0f});
	MeshData.FindChecked(Block).UV.Add(FVector2D{1.0f, 1.0f});
	MeshData.FindChecked(Block).UV.Add(FVector2D{0.0f, 1.0f});
}

void AVCVoxelChunk::AddIndices(EVCBlockType Block)
{
	const uint32 VertexCount = VertexCounts.FindChecked(Block);
	MeshData.FindChecked(Block).Indices.Add(VertexCount + 3); //TODO : get them once and then use
	MeshData.FindChecked(Block).Indices.Add(VertexCount + 2);
	MeshData.FindChecked(Block).Indices.Add(VertexCount);
	MeshData.FindChecked(Block).Indices.Add(VertexCount + 2);
	MeshData.FindChecked(Block).Indices.Add(VertexCount + 1);
	MeshData.FindChecked(Block).Indices.Add(VertexCount);
}

bool AVCVoxelChunk::CheckNone(FVector Position)
{
	if (Position.X >= ChunkSize || Position.Y >= ChunkSize || Position.Z >= ChunkSize || Position.X < 0.0f || Position.Y < 0.0f ||
		Position.Z < 0.0f)
		return true;

	return Blocks[GetBlockIndex(static_cast<int32>(Position.X), static_cast<int32>(Position.Y)
	                            , static_cast<int32>(Position.Z))] == EVCBlockType::None;
}

UMaterialInterface* AVCVoxelChunk::GetMaterialInterfaceFromBlock(EVCBlockType Block) const
{
	UVCGameInstance* GameInstance = Cast<UVCGameInstance>(GetGameInstance());
	if (!GameInstance)
		return nullptr;

	return GameInstance->Materials.FindChecked(Block);
}

void AVCVoxelChunk::ModifyChunkMesh(const FIntVector& Position, const EVCBlockType Block)
{
	if (Position.X >= BlockSize || Position.Y >= BlockSize || Position.Z >= BlockSize || Position.X < 0 || Position.Y < 0 || Position.Z
		< 0 || (!BlockVariety.Contains(Block) && Block != EVCBlockType::None)) //TODO: adding different blocks
		return;

	const int32 Index = GetBlockIndex(Position.X, Position.Y, Position.Z);
	Blocks[Index] = Block;

	ClearMesh();

	GenerateMesh();

	ApplyMesh();
}