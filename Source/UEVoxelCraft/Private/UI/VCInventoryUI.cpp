// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VCInventoryUI.h"
#include "UI/VCItemSlotUI.h"
#include "Inventory/VCInventoryComponent.h"
#include "Inventory/VCItemDataAsset.h"
#include "Inventory/VCItemSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

UVCInventoryUI::UVCInventoryUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), Columns{0}, SlotClass{nullptr},
                                                                              InventoryCompOwner{nullptr}, GridPanel{nullptr}
{
}

// FUNCTIONS

void UVCInventoryUI::InitializeWidget()
{
	checkf(SlotClass, TEXT("UI failed to get slot class"));
	checkf(InventoryCompOwner.IsValid(), TEXT("UI failed to specify owner"));
	checkf(GridPanel, TEXT("UI failed to get uniform grid panel"));

	SlotCount = InventoryCompOwner.Get()->GetSlotsNum();

	GridPanel->ClearChildren();

	const int32 RowCount = SlotCount / Columns;

	for (uint8 Row = 0; Row < RowCount; ++Row)
	{
		for (uint8 Col = 0; Col < Columns; ++Col)
		{
			if (Row + (Col * RowCount) == SlotCount)
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

void UVCInventoryUI::UpdateUI() const
{
	for (int Index = 0; Index < SlotCount; ++Index)
	{
		UpdateUIAt(Index);
	}
}

void UVCInventoryUI::UpdateUIAt(const int Index) const
{
	UVCItemSlotUI* SlotUI = Cast<UVCItemSlotUI>(GridPanel->GetChildAt(Index));
	if (SlotUI)
	{
		SlotUI->SlotNumber->SetText(FText::AsNumber(Index + 1));
		const UVCItemSlot& ItemSlot = InventoryCompOwner.Get()->GetSlot(Index);
		SlotUI->ItemCount->SetText(FText::AsNumber(ItemSlot.GetSlotItemCount()));
		if (IsValid(ItemSlot.GetItem()))
		{
			SlotUI->SetToolTipText(ItemSlot.GetItem()->GetItemDescription());
			SlotUI->ItemIcon->SetBrushFromTexture(ItemSlot.GetItem()->GetItemIcon(), true);
		}
		else
		{
			SlotUI->SetToolTipText(FText::FromString("Empty Slot"));
			SlotUI->ItemIcon->SetBrushFromTexture(nullptr, true);
		}
	}
}

void UVCInventoryUI::SetOwner(UVCInventoryComponent* InOutOwner)
{
	InventoryCompOwner = InOutOwner;
}
