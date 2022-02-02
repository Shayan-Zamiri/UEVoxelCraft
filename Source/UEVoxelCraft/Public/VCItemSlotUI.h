// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VCItemSlotUI.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class UEVOXELCRAFT_API UVCItemSlotUI : public UUserWidget
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UVCItemSlotUI(const FObjectInitializer& ObjectInitializer);

	// FUNCTIONS
public:
	// GETTERS & SETTERS
public:
	// PROPERTIES
public:
	UPROPERTY(BlueprintReadWrite, Category= "Properties", meta= (BindWidget))
	UTextBlock* SlotNumber;
	
	UPROPERTY(BlueprintReadWrite, Category= "Properties", meta= (BindWidget))
	UTextBlock* ItemCount;

	UPROPERTY(BlueprintReadWrite, Category= "Properties", meta= (BindWidget))
	UTextBlock* ItemDescription;

	UPROPERTY(BlueprintReadWrite, Category= "Properties", meta= (BindWidget))
	UImage* ItemIcon;
};
