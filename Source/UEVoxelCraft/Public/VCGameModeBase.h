// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VCGameModeBase.generated.h"

class AVCProceduralGenerator;

UCLASS(Blueprintable)
class UEVOXELCRAFT_API AVCGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AVCGameModeBase();
	
	virtual ~AVCGameModeBase() override;
	
protected:
	virtual void BeginPlay() override;
	
	// FUNCTIONS
public:
	
	// GETTERS & SETTERS
public:
	AVCProceduralGenerator* GetProceduralGenerator();
	
	// PROPERTIES
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category= "Propeties")
	TSubclassOf<AVCProceduralGenerator> ProceduralGeneratorClass;

	UPROPERTY()
	AVCProceduralGenerator* ProceduralGenerator;
};
