﻿#pragma once

#include "CoreMinimal.h"
#include "VCTypes.h"
#include "VCProceduralGenerator.generated.h"

class AVCBaseBlock;

UCLASS(Blueprintable)
class UEVOXELCRAFT_API AVCProceduralGenerator : public AActor
{
	GENERATED_BODY()
	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AVCProceduralGenerator();
	
	virtual ~AVCProceduralGenerator() override = default;
	
	// FUNCTIONS
public:
	void Generate();

	// GETTERS & SETTERS
	UInstancedStaticMeshComponent* GetInstancedStaticMeshComponent();
	
	// PROPERTIES
public:
	static TArray<FVCBiomes> Biomes;

protected:
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category= "Properties")
	TSubclassOf<AVCBaseBlock> BlockClass;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category= "Properties")
	UInstancedStaticMeshComponent* ISMComp;

	UPROPERTY(EditDefaultsOnly, Category= "Properties")
	UStaticMesh* StaticMesh;
	
	UPROPERTY(EditDefaultsOnly, Category= "Properties")
	int32 MapSize;

	UPROPERTY(VisibleAnywhere, Category= "Properties")
	int32 RandomSeed;

	// Think of this as a zoom level
	UPROPERTY(EditDefaultsOnly, Category= "Properties")
	float Frequency;

	// Scale or intensity of the noise
	UPROPERTY(EditDefaultsOnly, Category= "Properties")
	float Amplitude;
};
