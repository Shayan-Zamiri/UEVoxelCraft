#pragma once

#include "CoreMinimal.h"
#include "VCTypes.h"
#include "VCProceduralGenerator.generated.h"

class AVCBaseBlock;

UCLASS(Blueprintable)
class UEVOXELCRAFT_API UVCProceduralGenerator : public UObject
{
	GENERATED_BODY()
	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UVCProceduralGenerator();
	virtual ~UVCProceduralGenerator() override = default;

	// FUNCTIONS
public:
	void Generate();

	// GETTERS & SETTERS
public:
	// PROPERTIES
public:
	static TArray<FVCBiomes> Biomes;

protected:
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category= "Properties")
	TArray<TSubclassOf<AVCBaseBlock>> BlockClasses;

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
