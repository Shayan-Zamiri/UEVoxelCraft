// Fill out your copyright notice in the Description page of Project Settings.


#include "VCInventoryComponent.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS 

// Sets default values for this component's properties
UVCInventoryComponent::UVCInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

UVCInventoryComponent::~UVCInventoryComponent()
{
	ItemsStrongReferences.Empty();
	ItemSlotsStrongReferences.Empty();
	InventorySlots.Empty();
	InventoryData.Empty();
}


// Called when the game starts
void UVCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InventorySlotsInitializer();
	EquippedSlot = InventorySlots.FindChecked(1).Key;
}

// FUNCTIONS

