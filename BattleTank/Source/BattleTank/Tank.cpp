// RebusStudios 2019

#include "Tank.h"


#include "Engine/World.h"
#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values
ATank::ATank()
{	

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	// calling super will return damage with falloff (if set)
	auto RoundDamage = FPlatformMath::RoundToInt(Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser));
	int32 DamageToApply = FMath::Clamp<int32>(RoundDamage, 0.0, CurrentHealth);
	UE_LOG(LogTemp, Warning, TEXT("Tank %s Health at %i taking damage %i of %i"),*GetName(),CurrentHealth,DamageToApply, RoundDamage);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank %s died!"), *GetName());
	}

	return (float)DamageToApply;
}
