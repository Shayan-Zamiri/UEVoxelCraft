// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VCInventoryComponent.generated.h"


UCLASS(ClassGroup=(VoxelCraft), meta=(BlueprintSpawnableComponent))
class UEVOXELCRAFT_API UVCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UVCInventoryComponent();

	virtual ~UVCInventoryComponent() override;
	
protected:
	virtual void BeginPlay() override;

	// FUNCTIONS
public:

	// GETTERS & SETTERS
public:

	// PROPERTIES
protected:
	
};
