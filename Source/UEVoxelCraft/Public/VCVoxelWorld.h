﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VCVoxelWorld.generated.h"

class AVCVoxelChunk;

UCLASS()
class UEVOXELCRAFT_API AVCVoxelWorld : public AActor
{
	GENERATED_BODY()

public:
	AVCVoxelWorld();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category= "Properties")
	int32 DrawDistance;

	UPROPERTY(EditAnywhere, Category= "Properties")
	TSubclassOf<AVCVoxelChunk> VoxelChunkClass;
};