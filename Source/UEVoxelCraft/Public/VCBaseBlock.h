#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VCBaseBlock.generated.h"

class UBoxComponent;
class AVCProceduralGenerator;

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

protected:
	FVector GetAttachLocation(const FVector& ClickedLocation, const FVector& Normal) const;
	
	void GridSnapBlock();

	void RemoveInstancedMesh() const;

	void MoveInstancedMesh(const FTransform& NewTransform) const;
	
	// GETTERS & SETTERS
public:
	void SetStaticMeshInstanceID(int32 Index);

	// PROPERTIES
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Components")
	USceneComponent* RootSceneComp;

	// for collision data
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Components")
	UBoxComponent* BoxComp;

	UPROPERTY()
	TWeakObjectPtr<AVCProceduralGenerator> ProceduralGenerator;
	
	static float BlockSize; // ex:100 100 100

protected:
	int32 SMInstanceIndex;
	
	float bIsBreakable; // TODO: Health Component
};
