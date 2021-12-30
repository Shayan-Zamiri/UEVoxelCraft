// Copyright Epic Games, Inc. All Rights Reserved.


#include "VCGameModeBase.h"
#include "VCProceduralGenerator.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS


AVCGameModeBase::AVCGameModeBase() : ProceduralGeneratorClass{nullptr}, ProceduralGenerator{nullptr} {}

AVCGameModeBase::~AVCGameModeBase() {}

void AVCGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (ProceduralGeneratorClass)
	{
		ProceduralGenerator = GetWorld()->SpawnActor<AVCProceduralGenerator>(ProceduralGeneratorClass, FVector{}, FRotator{});
		if (ProceduralGenerator)
		{
			ProceduralGenerator->Generate();
		}
	}
}

AVCProceduralGenerator* AVCGameModeBase::GetProceduralGenerator()
{
	return IsValid(ProceduralGenerator) ? ProceduralGenerator : nullptr; 
}
