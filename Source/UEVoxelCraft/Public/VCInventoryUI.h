// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VCInventoryUI.generated.h"

class UVCInventoryComponent;
class UUniformGridPanel;

/**
 * 
 */
UCLASS()
class UEVOXELCRAFT_API UVCInventoryUI : public UUserWidget
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UVCInventoryUI(const FObjectInitializer& ObjectInitializer);

	// FUNCTIONS
public:
	UFUNCTION(BlueprintCallable, Category= "UI")
	void InitializeWidget();

	UFUNCTION(BlueprintCallable, Category= "UI")
	void UpdateUI();

	// PROPERTIES
protected:
	UPROPERTY(EditDefaultsOnly, Category= "Properties")
	TSubclassOf<UUserWidget> SlotClass;

	UPROPERTY(EditAnywhere, Category= "Properties")
	int32 Columns;

	TWeakObjectPtr<UVCInventoryComponent> Owner;

	UPROPERTY(BlueprintReadWrite, meta= (BindWidget))
	UUniformGridPanel* GridPanel;
};
