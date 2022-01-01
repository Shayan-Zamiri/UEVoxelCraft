#include "VCProceduralGenerator.h"
#include "VCBaseBlock.h"
#include "VCPGWorker.h"

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
	const int32 MapSizeHalf = MapSize / 2;

	FVCPGWorker* PGWorker = new FVCPGWorker{this, MapSizeHalf, RandomSeed, Frequency, Amplitude};

	while (!PGWorker->bCompleteTask || !SpawnLocations.IsEmpty())
	{
		FVector SpawnLocation{};
		if (SpawnLocations.Dequeue(SpawnLocation))
		{
			AVCBaseBlock* SpawnedBlock = GetWorld()->SpawnActor<AVCBaseBlock>(BlockClass, SpawnLocation, FRotator{});
			const int32 InstanceID = ISMComp->AddInstanceWorldSpace(
				FTransform{FVector{SpawnLocation + FVector{AVCBaseBlock::BlockSize / 2, AVCBaseBlock::BlockSize / 2, 0.0f}}});
			SpawnedBlock->SetStaticMeshInstanceID(InstanceID);
		}
	}

	delete PGWorker;
}

// GETTERS & SETTERS

UInstancedStaticMeshComponent* AVCProceduralGenerator::GetInstancedStaticMeshComponent()
{
	return ISMComp;
}
