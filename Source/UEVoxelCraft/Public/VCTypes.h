#pragma once

#include "VCTypes.generated.h"

// ENUMS

UENUM(BlueprintType)
enum class EVCBiomeType : uint8
{
	Desert,
	Forest,
	Ocean,
	Plain
	//...
};

// STRUCTS

USTRUCT(BlueprintType)
struct UEVOXELCRAFT_API FVCBiomes
{
	GENERATED_BODY()

	EVCBiomeType BiomeType;
	int8 Temperature;
	uint8 Rainfall; // 0 - 100
};

// DELEGATES

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnTakeDamageSignature, class UVCHealthComponent* HealthComponent, float CurrentHealth,
                                       AController* InstigatedBy);
