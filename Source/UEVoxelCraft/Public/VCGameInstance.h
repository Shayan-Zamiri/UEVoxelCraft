// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VCTypes.h"
#include "Engine/GameInstance.h"
#include "VCGameInstance.generated.h"

class UVCProceduralGenerator;

UCLASS()
class UEVOXELCRAFT_API UVCGameInstance : public UGameInstance
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UVCGameInstance();
	virtual ~UVCGameInstance() override;

protected:
	virtual void OnStart() override;

	// FUNCTIONS
public:
	// GETTERS & SETTERS
public:
	// PROPERTIES
public:
	UPROPERTY(EditDefaultsOnly,Category="Properties")
	TMap<EVCBlockType ,UMaterialInterface*> Materials;
};
