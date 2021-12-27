// Fill out your copyright notice in the Description page of Project Settings.


#include "VCGameInstance.h"

#include "VCProceduralGenerator.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

UVCGameInstance::UVCGameInstance() : ProceduralGeneratorClass{nullptr}, ProceduralGenerator{nullptr} {}

UVCGameInstance::~UVCGameInstance() {}

void UVCGameInstance::OnStart()
{
	Super::OnStart();

	if (ProceduralGeneratorClass)
	{
		ProceduralGenerator = NewObject<UVCProceduralGenerator>(this, ProceduralGeneratorClass);
		if (ProceduralGenerator)
		{
			ProceduralGenerator->Generate();
		}
	}
}
