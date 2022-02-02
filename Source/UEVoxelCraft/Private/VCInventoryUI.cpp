// Fill out your copyright notice in the Description page of Project Settings.


#include "VCInventoryUI.h"
#include "VCInventoryComponent.h"
#include "VCItemDataAsset.h"
#include "VCItemSlotUI.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

UVCInventoryUI::UVCInventoryUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), SlotClass{nullptr}, Columns{0},
                                                                        Owner{nullptr}, GridPanel{nullptr}
{
}

// FUNCTIONS

void UVCInventoryUI::InitializeWidget()
{
	checkf(SlotClass, TEXT("UI failed to get slot class"));
	checkf(!Owner.IsValid(), TEXT("UI failed to specify owner"));
	checkf(GridPanel, TEXT("UI failed to get uniform grid panel"));

	GridPanel->ClearChildren();
	
	const int32 SlotCount = Owner.Get()->GetSlotsNum();

	const int32 RowCount = SlotCount / Columns;

	for (uint8 Row = 0; Row < RowCount; ++Row)
	{
		for (uint8 Col = 0; Col < Columns; ++Col)
		{
			if (Row + ((Col + 1) * RowCount) == SlotCount)
			{
				return;
			}
			UUserWidget* ItemSlot = CreateWidget(GridPanel, SlotClass);
			if (ItemSlot)
			{
				UUniformGridSlot* GridSlot = GridPanel->AddChildToUniformGrid(ItemSlot, Row, Col);
				GridSlot->SetVerticalAlignment(VAlign_Center);
				GridSlot->SetHorizontalAlignment(HAlign_Center);
			}
		}
	}
}

void UVCInventoryUI::UpdateUI()
{
	UVCInventoryComponent* Inventory = Owner.Get();
	
	for (int Index = 0; Index < Owner.Get()->GetSlotsNum(); ++Index)
	{
		UUserWidget* Widget = Cast<UUserWidget>(GridPanel->GetChildAt(Index - 1));
		if (Widget)
		{
			UVCItemSlotUI* SlotUI = Cast<UVCItemSlotUI>(Widget);
			if (SlotUI)
			{
				SlotUI->ItemCount->SetText(FText::AsNumber(Inventory->GetItem(Index - 1)->GetItemCount()));
				SlotUI->SlotNumber->SetText(FText::AsNumber(Index));
				SlotUI->ItemDescription->SetToolTipText(Inventory->GetItem(Index - 1)->GetItemDescription());
				// TODO: Load required assets
				SlotUI->ItemIcon->SetBrushFromTexture(Inventory->GetItem(Index - 1)->GetItemIcon(), true);
			}
		}
	}
}
