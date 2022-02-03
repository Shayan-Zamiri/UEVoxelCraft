// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VCInventoryUI.generated.h"

class UVCInventoryComponent;
class UUniformGridPanel;
class UVCItemDataAsset;
class UVCItemSlotUI;

UCLASS(Abstract)
class UEVOXELCRAFT_API UVCInventoryUI : public UUserWidget
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UVCInventoryUI(const FObjectInitializer& ObjectInitializer);

	// FUNCTIONS
public:
	void InitializeWidget();

	void UpdateUI();

	void UpdateUIAt(const int Index);

	void SetOwner(UVCInventoryComponent* InOutOwner);
protected:
	// PROPERTIES
	UPROPERTY(EditAnywhere, Category= "Properties")
	int32 Columns;

	UPROPERTY(VisibleAnywhere, Category= "Properties")
	int32 SlotCount;

	UPROPERTY(EditDefaultsOnly, Category= "Properties")
	TSubclassOf<UVCItemSlotUI> SlotClass;

	TWeakObjectPtr<UVCInventoryComponent> InventoryCompOwner;

	UPROPERTY(BlueprintReadWrite, meta= (BindWidget))
	UUniformGridPanel* GridPanel;
};
