// Fill out your copyright notice in the Description page of Project Settings.


#include "VCInventoryComponent.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS 

UVCInventoryComponent::UVCInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UVCInventoryComponent::~UVCInventoryComponent()
{
	ItemsStrongReferences.Empty();
	ItemSlotsStrongReferences.Empty();
	InventorySlots.Empty();
	InventoryData.Empty();
}

void UVCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

// FUNCTIONS

