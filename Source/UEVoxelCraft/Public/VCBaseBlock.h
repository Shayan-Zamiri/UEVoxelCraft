#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VCBaseBlock.generated.h"

class UBoxComponent;

UCLASS(Abstract, Blueprintable, BlueprintType)
class UEVOXELCRAFT_API AVCBaseBlock : public AActor
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AVCBaseBlock();

	virtual ~AVCBaseBlock() override = default;

	virtual void OnConstruction(const FTransform& Transform) override;

	// FUNCTIONS
public:
	FVector GetCenterOfCube() const;
	
	static FVector GetAttachLocation(const FVector& ClickedLocation, const FVector& Normal);

	void GridSnapBlock();

	// GETTERS & SETTERS
public:
	// PROPERTIES
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Components")
	USceneComponent* RootSceneComp;

	// doesn't have collision
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Components")
	UStaticMeshComponent* SMComp;

	// for collision data
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Components")
	UBoxComponent* BoxComp;

	static float BlockSize; // ex:100 100 100

protected:
	float bIsBreakable; // TODO: Health Component
};
