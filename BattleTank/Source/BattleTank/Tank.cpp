// RebusStudios 2019

#include "Tank.h"


#include "Engine/World.h"
#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values
ATank::ATank()
{	
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = InitialHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	// calling super will return damage with falloff (if set)
	auto RoundDamage = FPlatformMath::RoundToInt(Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser));
	int32 DamageToApply = FMath::Clamp<int32>(RoundDamage, 0.0, CurrentHealth);
	//UE_LOG(LogTemp, Warning, TEXT("Tank %s Health at %i taking damage %i of %i"),*GetName(),CurrentHealth,DamageToApply, RoundDamage);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return (float)DamageToApply;
}

const float ATank::GetHealthPercent()
{
	return ((float)CurrentHealth/(float)InitialHealth);
}