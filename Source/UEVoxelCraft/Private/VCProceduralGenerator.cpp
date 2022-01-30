#include "VCProceduralGenerator.h"
#include "VCBaseBlock.h"
#include "VCPGWorker.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

AVCProceduralGenerator::AVCProceduralGenerator() : MapSize{128}, RandomSeed{0}, Frequency{20.0f},
                                                   Amplitude{10.0f}, bIsGenerationComplete{false}, PGWorker{nullptr}
{
	PrimaryActorTick.bCanEverTick = true;
	ISMComp = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
	ISMComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AVCProceduralGenerator::BeginPlay()
{
	Super::BeginPlay();
	RandomSeed = FMath::RandRange(1000, 9999);
	PGWorker = new FVCPGWorker{this, MapSize / 2, RandomSeed, Frequency, Amplitude};
	if (StaticMesh)
		ISMComp->SetStaticMesh(StaticMesh);
}

void AVCProceduralGenerator::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!bIsGenerationComplete)
	{
		Generate();
	}
}

// FUNCTIONS

void AVCProceduralGenerator::Generate()
{
	if (!BlockClass)
		return;

	FVector SpawnLocation{};
	if (SpawnLocations.Dequeue(SpawnLocation))
	{
		AVCBaseBlock* SpawnedBlock = GetWorld()->SpawnActor<AVCBaseBlock>(BlockClass, SpawnLocation, FRotator{});
		const int32 InstanceID = ISMComp->AddInstanceWorldSpace(
			FTransform{FVector{SpawnLocation + FVector{AVCBaseBlock::BlockSize / 2, AVCBaseBlock::BlockSize / 2, 0.0f}}});
		SpawnedBlock->SetStaticMeshInstanceID(InstanceID);
	}

	if (SpawnLocations.IsEmpty())
		bIsGenerationComplete = true;


	if (bIsGenerationComplete)
	{
		delete PGWorker;
	}
}

// GETTERS & SETTERS

UInstancedStaticMeshComponent* AVCProceduralGenerator::GetInstancedStaticMeshComponent()
{
	return ISMComp;
}
