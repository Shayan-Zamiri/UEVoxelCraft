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

	virtual void OnConstruction(const FTransform& Transform) override;

	// FUNCTIONS
public:
	FVector GetCenterOfCube() const;

	static FVector GetAttachLocation(const FVector& ClickedLocation, const FVector& Normal);

	void GridSnapBlock();

	/** A wrapper for HealthComp->HandleTakeDamage(...)*/
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
										  AActor* DamageCauser);

	// GETTERS & SETTERS
public:
	// PROPERTIES
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
