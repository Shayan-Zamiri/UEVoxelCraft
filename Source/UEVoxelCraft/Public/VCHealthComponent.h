// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VCTypes.h"
#include "Components/ActorComponent.h"
#include "VCHealthComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEVOXELCRAFT_API UVCHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	UVCHealthComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	// FUNCTIONS
public:
	UFUNCTION()
	void HandleTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
	                      AActor* DamageCauser);


	// GETTERS & SETTERS
public:
	float GetCurrentHealth() const;

	void  SetCurrentHealth(float InCurrentHealth) ;
	
	float GetDefaultHealth() const;

	void SetDefaultHealth(float InDefaultHealth) ;
	
	// PROPERTIES
public:
	/** Any function that wants to know about the actor being damaged must be bound to this */
	FOnTakeDamageSignature OnTakeDamage;

protected:
	/** Default health used when we want to reset the actor's health or as a base for HUD progress bars */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Properties")
	float DefaultHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Properties")
	float CurrentHealth;
};
