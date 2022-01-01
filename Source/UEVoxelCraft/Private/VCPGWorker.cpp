// Fill out your copyright notice in the Description page of Project Settings.


#include "VCPGWorker.h"

#include "VCBaseBlock.h"
#include "VCProceduralGenerator.h"


#pragma region Main Thread Code
// This code will be run on the thread that invoked this thread (i.e. game thread)

FVCPGWorker::FVCPGWorker(AVCProceduralGenerator* InOutProceduralGenerator, int32 InMapSizeHalf,
                         int32 InRandomSeed, float InFrequency, float InAmplitude)
	: MapSizeHalf{InMapSizeHalf}, RandomSeed{InRandomSeed}, Frequency{InFrequency}, Amplitude{InAmplitude}
{
	ProceduralGenerator = InOutProceduralGenerator;
	Thread = FRunnableThread::Create(this,TEXT("FVCPGWorker"/*ProceduralGenerationThread*/));
}

FVCPGWorker::~FVCPGWorker()
{
	if (Thread)
	{
		Thread->Kill();
		delete Thread;
	}
}
#pragma endregion

bool FVCPGWorker::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("My Procedural Generation thread has been initialized"))

	bRunThread = true;

	bCompleteTask = false;

	return true;
}

uint32 FVCPGWorker::Run()
{
	if (bRunThread)
	{
		for (int32 x = -MapSizeHalf; x < MapSizeHalf; x++)
		{
			for (int32 y = -MapSizeHalf; y < MapSizeHalf; y++)
			{
				const float fX = static_cast<float>(x);
				const float fY = static_cast<float>(y);
				const FVector2D Location2D{fX, fY};
				const float Height = FMath::PerlinNoise2D((Location2D + RandomSeed) / Frequency) * Amplitude;
				FVector SpawnLocation{fX, fY, Height};
				SpawnLocation *= 100.0f;
				ProceduralGenerator->SpawnLocations.Enqueue(SpawnLocation.GridSnap(AVCBaseBlock::BlockSize));
			}
		}
		bCompleteTask = true;
	}
	return 0;
}

void FVCPGWorker::Stop()
{
	bRunThread = false;
}
