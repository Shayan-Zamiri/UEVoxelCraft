#include "VCProceduralGenerator.h"

#include "VCBaseBlock.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

UVCProceduralGenerator::UVCProceduralGenerator() : MapSize{128}, RandomSeed{0}, Frequency{20.0f}, Amplitude{10.0f}
{
}

// FUNCTIONS

void UVCProceduralGenerator::Generate()
{
	if (BlockClasses.Num() < 1) // Check is there any BlockClasses to spawn
		return;
	
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
			GetWorld()->SpawnActor<AVCBaseBlock>(BlockClasses[0], SpawnLocation, FRotator{});
		}
	}
}
