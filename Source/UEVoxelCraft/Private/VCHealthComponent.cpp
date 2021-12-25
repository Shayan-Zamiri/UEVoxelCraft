// Fill out your copyright notice in the Description page of Project Settings.


#include "VCHealthComponent.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

// Sets default values for this component's properties
UVCHealthComponent::UVCHealthComponent() : DefaultHealth{0.0f}, CurrentHealth{0.0f}
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVCHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
		Owner->OnTakeAnyDamage.AddDynamic(this, &UVCHealthComponent::HandleTakeDamage);

	CurrentHealth = DefaultHealth;
}

// Called every frame
void UVCHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
