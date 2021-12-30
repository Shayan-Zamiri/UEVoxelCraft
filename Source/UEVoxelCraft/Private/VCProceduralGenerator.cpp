#include "VCProceduralGenerator.h"
#include "VCBaseBlock.h"

// STATICS

TArray<FVCBiomes> AVCProceduralGenerator::Biomes
{
	FVCBiomes{EVCBiomeType::Desert, 100, 0},
	FVCBiomes{EVCBiomeType::Forest, 35, 80},
	FVCBiomes{EVCBiomeType::Ocean, 25, 50},
	FVCBiomes{EVCBiomeType::Plain, 40, 40}
};

// CTOR/DTOR & VIRTUAL FUNCTIONS

AVCProceduralGenerator::AVCProceduralGenerator() : MapSize{128}, RandomSeed{0}, Frequency{20.0f}, Amplitude{10.0f}
{
	ISMComp = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
	ISMComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// FUNCTIONS

void AVCProceduralGenerator::Generate()
{
	if (!ISMComp || !BlockClass || !StaticMesh)
		return;

	ISMComp->SetStaticMesh(StaticMesh);

	RandomSeed = FMath::RandRange(1000, 9999);
	const float MapSizeHalf = MapSize / 2;
	for (int32 x = -MapSizeHalf; x < MapSizeHalf; x++)
	{
		for (int32 y = -MapSizeHalf; y < MapSizeHalf; y++)
		{
			const float fX = static_cast<float>(x);
			const float fY = static_cast<float>(y);
			const FVector2D Location2D{fX, fY};
			const float Height = FMath::PerlinNoise2D((Location2D + RandomSeed) / Frequency) * Amplitude;
			FVector SpawnLocation{fX, fY, Height};
			SpawnLocation *= AVCBaseBlock::BlockSize;
			AVCBaseBlock* SpawnedBlock = GetWorld()->SpawnActor<AVCBaseBlock>(BlockClass, SpawnLocation, FRotator{});
			const int32 InstanceID = ISMComp->AddInstance(
				FTransform{FVector{SpawnLocation.GridSnap(AVCBaseBlock::BlockSize) + FVector{AVCBaseBlock::BlockSize / 2, AVCBaseBlock::BlockSize / 2, 0.0f}}});
			SpawnedBlock->SetStaticMeshInstanceID(InstanceID);
		}
	}
}

// GETTERS & SETTERS

UInstancedStaticMeshComponent* AVCProceduralGenerator::GetInstancedStaticMeshComponent()
{
	return ISMComp;
}
