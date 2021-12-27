#pragma once

#include "VCTypes.generated.h"

UENUM(BlueprintType)
enum class EVCBiomeType : uint8
{
	Desert,
	Forest,
	Ocean,
	Plain
	//...
};

USTRUCT(BlueprintType)
struct UEVOXELCRAFT_API FVCBiomes
{
	GENERATED_BODY()
	
	EVCBiomeType BiomeType;
	int8 Temperature;
	uint8 Rainfall;   // 0 - 100
};