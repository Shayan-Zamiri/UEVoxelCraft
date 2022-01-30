#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VCBaseBlock.generated.h"

class UBoxComponent;
class UVCHealthComponent;

UCLASS(Abstract, Blueprintable, BlueprintType)
class UEVOXELCRAFT_API AVCBaseBlock : public AActor
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	AVCBaseBlock();
	
	virtual ~AVCBaseBlock() override = default;
	

	virtual ~AVCBaseBlock() override = default;

	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual float TakeDamage(float DamageAmount,  const FDamageEvent& DamageEvent, AController* EventInstigator,
	                        AActor* DamageCauser) override;

	// FUNCTIONS
public:
	FVector GetCenterOfCube() const;

protected:
	FVector GetAttachLocation(const FVector& ClickedLocation, const FVector& Normal) const;
	
	static FVector GetAttachLocation(const FVector& ClickedLocation, const FVector& Normal);

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
public:
	static float BlockSize; // ex:100 100 100

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Properties|Components")
	USceneComponent* RootSceneComp;

	/** Doesn't have collision */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Properties|Components")
	UStaticMeshComponent* SMComp;

	/** For collision data */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Properties|Components")
	UBoxComponent* BoxComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Properties|Components")
	UVCHealthComponent* HealthComp;
};
