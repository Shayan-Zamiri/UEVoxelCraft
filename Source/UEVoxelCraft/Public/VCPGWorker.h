// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AVCProceduralGenerator;

/**
 * Procedural Generation Worker
 */
class FVCPGWorker : FRunnable
{
	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	FVCPGWorker(AVCProceduralGenerator* InOutProceduralGenerator, int32 InMapSizeHalf,
	            int32 InRandomSeed, float InFrequency, float InAmplitude);

	virtual ~FVCPGWorker() override;

	virtual bool Init() override;

	virtual uint32 Run() override;

	virtual void Stop() override;


	// PROPERTIES
public:
	bool bCompleteTask;

private:
	int32 MapSizeHalf;
	int32 RandomSeed;
	float Frequency;
	float Amplitude;
	
	FRunnableThread* Thread;
	bool bRunThread;
	AVCProceduralGenerator* ProceduralGenerator;
};
