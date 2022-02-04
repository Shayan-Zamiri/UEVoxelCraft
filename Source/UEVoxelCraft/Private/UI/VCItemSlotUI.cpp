// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/VCItemSlotUI.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

UVCItemSlotUI::UVCItemSlotUI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), SlotNumber{nullptr}, ItemCount{nullptr}, ItemIcon{nullptr}
{
}
