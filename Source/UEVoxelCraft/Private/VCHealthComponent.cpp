// Fill out your copyright notice in the Description page of Project Settings.


#include "VCHealthComponent.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

UVCHealthComponent::UVCHealthComponent() : DefaultHealth{0.0f}, CurrentHealth{0.0f}
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UVCHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
		Owner->OnTakeAnyDamage.AddDynamic(this, &UVCHealthComponent::HandleTakeDamage);

	CurrentHealth = DefaultHealth;
}

void UVCHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// FUNCTIONS

void UVCHealthComponent::HandleTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0)
		return;

	CurrentHealth -= Damage;

	/** Handles calling bound functions. Observer desgin pattern */
	OnTakeDamage.Broadcast(this, CurrentHealth, InstigatedBy);
}
