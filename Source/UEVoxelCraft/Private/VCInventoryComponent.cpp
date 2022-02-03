// Fill out your copyright notice in the Description page of Project Settings.


#include "VCInventoryComponent.h"
#include "VCInventoryUI.h"
#include "VCItemSlot.h"
#include "VCItemDataAsset.h"

// STATICS

// CTOR/DTOR & VIRTUAL FUNCTIONS 

UVCInventoryComponent::UVCInventoryComponent() : SlotCount{10}, InventoryUIClass{nullptr}, InventoryUI{nullptr}
{
	PrimaryComponentTick.bCanEverTick = false;
	InventorySlotsInitializer();
}

UVCInventoryComponent::~UVCInventoryComponent()
{
	InventorySlots.Empty();
	InventoryData.Empty();
}

void UVCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	InventoryUI = Cast<UVCInventoryUI>(CreateWidget(GetWorld(), InventoryUIClass,TEXT("InventoryUI")));
	check(InventoryUI);
	InventoryUI->SetOwner(this);
	InventoryUI->InitializeWidget();
	InventoryUI->UpdateUI();
}

// FUNCTIONS

void UVCInventoryComponent::AddItem(const FPrimaryAssetId& InItemID, int32 Count)
{
	UVCItemSlot* Slot = FindAppropriateSlot(InItemID);
	if (!Slot)
		return;

	if (InventoryData.Contains(InItemID))
	{
		UVCItemDataAsset* Item = InventoryData.FindChecked(InItemID);
		Item->SetItemCount(Item->GetItemCount() + Count);
		Slot->SetSlotItemCount(Count);
	}
	else
	{
		LoadAndAddItem(InItemID, Slot->GetSlotNumber(), Count);
	}
}

bool UVCInventoryComponent::ContainsItem(const FPrimaryAssetId& InItemID) const
{
	return InventoryData.Contains(InItemID);
}

void UVCInventoryComponent::UpdateInventoryUI()
{
	InventoryUI->UpdateUI();
}

void UVCInventoryComponent::ShowInventory()
{
	InventoryUI->AddToViewport();
}

void UVCInventoryComponent::HideInventory()
{
	InventoryUI->RemoveFromViewport();
}

void UVCInventoryComponent::DecreaseItemSlotCount(int32 SlotNumber, int32 Count)
{
	UVCItemSlot& Slot = GetSlot(SlotNumber);
	if (Slot.IsSlotEmpty())
		return;

	Slot.SetSlotItemCount(Count == 0 ? 0 : Slot.GetSlotItemCount() - Count);
}

void UVCInventoryComponent::IncreaseItemSlotCount(int32 SlotNumber, int32 Count)
{
	UVCItemSlot& Slot = GetSlot(SlotNumber);
	if (Slot.IsSlotEmpty())
		return;

	Slot.SetSlotItemCount(Count == 0 ? Slot.GetItem()->GetMaxItemCount() : Slot.GetSlotItemCount() + Count);
}

void UVCInventoryComponent::InsertInSlot(int32 SlotNumber, int32 Count, UVCItemDataAsset* InItem)
{
	check(IsValid(InItem));
	GetSlot(SlotNumber).SetItem(InItem);
	GetSlot(SlotNumber).SetSlotItemCount(Count);
}

UVCItemSlot* UVCInventoryComponent::FindEmptySlot()
{
	for (const auto& It : InventorySlots)
	{
		if (It->IsSlotEmpty())
		{
			return It;
		}
	}

	return nullptr;
}

UVCItemSlot* UVCInventoryComponent::FindAppropriateSlot(const FPrimaryAssetId& AssetID)
{
	bool bIsEmptySlotFounded = false;
	UVCItemSlot* ReturnSlot = nullptr;
	for (const auto& It : InventorySlots)
	{
		const UVCItemDataAsset* Item = It->GetItem();
		// Appropriate Stackable Slot
		if (IsValid(Item) && Item->GetPrimaryAssetId() == AssetID && It->GetSlotItemCount() < It->GetSlotMaxCount())
		{
			ReturnSlot = It;
			break;
		}
		// Appropriate Empty Slot
		if (!bIsEmptySlotFounded && It->GetSlotItemType() == AssetID.PrimaryAssetType && It->IsSlotEmpty())
		{
			ReturnSlot = It;
			bIsEmptySlotFounded = true;
		}
	}
	return ReturnSlot;
}

UVCItemSlot& UVCInventoryComponent::GetSlot(int32 SlotNumber)
{
	checkf(SlotNumber > 0 || SlotNumber < GetSlotsNum(), TEXT("SlotNumber is out of range"));
	return *InventorySlots[SlotNumber];
}

int32 UVCInventoryComponent::GetSlotsNum() const { return InventorySlots.Num(); }

bool UVCInventoryComponent::IsSlotValid(const UVCItemSlot* InItemSlot) const
{
	check(IsValid(InItemSlot));
	return InventorySlots.Contains(InItemSlot) && InItemSlot->IsSlotValid();
}

bool UVCInventoryComponent::IsSlotEmpty(int32 SlotNumber)
{
	return GetSlot(SlotNumber).IsSlotEmpty();
}

const UVCItemDataAsset* UVCInventoryComponent::GetItem(int32 SlotNumber)
{
	return GetSlot(SlotNumber).GetItem();
}

void UVCInventoryComponent::AddItemToInventoryData(const FPrimaryAssetId& InItemID, UVCItemDataAsset* InOutItemDA)
{
	check(!InventoryData.Contains(InItemID));
	InventoryData.Add(InItemID, InOutItemDA);
}

void UVCInventoryComponent::RemoveItemFromInventoryData(const FPrimaryAssetId& InItemID, int32 Count)
{
	UVCItemDataAsset** PointerToItem = InventoryData.Find(InItemID);
	if (!PointerToItem)
		return;

	UVCItemDataAsset* Item = *PointerToItem;

	if (Item->GetItemCount() - Count <= 0)
	{
		InventoryData.Remove(InItemID);
	}
	else
	{
		Item->SetItemCount(Item->GetItemCount() - Count);
	}
}

void UVCInventoryComponent::LoadAndAddItem(const FPrimaryAssetId& InItemID, int32 SlotNumber, int32 Count)
{
	UVCAssetManager& AssetManager = UVCAssetManager::Get();
	const FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &UVCInventoryComponent::OnLoadItem, InItemID, SlotNumber,
	                                                                        Count);
	AssetManager.LoadPrimaryAsset(InItemID, TArray<FName>{}, Delegate);
}

void UVCInventoryComponent::OnLoadItem(FPrimaryAssetId ItemID, int32 SlotNumber, int32 Count)
{
	const UVCAssetManager& AssetManager = UVCAssetManager::Get();
	UObject* Object = AssetManager.GetPrimaryAssetObject(ItemID);
	if (!IsValid(Object))
		return;

	UVCItemDataAsset* Item = Cast<UVCItemDataAsset>(Object);
	Item->SetItemCount(Count);
	AddItemToInventoryData(ItemID, Item);
	InsertInSlot(SlotNumber, Count, Item);
	UpdateInventoryUI();
}

void UVCInventoryComponent::InventorySlotsInitializer()
{
	for (int32 i = 0; i < SlotCount; i++)
	{
		FString Name{"Slot"};
		Name.AppendInt(i);
		UVCItemSlot* ItemSlot = CreateDefaultSubobject<UVCItemSlot>(FName{Name});
		ItemSlot->SetSlotNumber(i);
		ItemSlot->SetSlotItemType(UVCAssetManager::InventoryItem);
		ItemSlot->SetSlotItemCount(0);
		ItemSlot->SetItem(nullptr);
		InventorySlots.Add(ItemSlot);
	}
}
