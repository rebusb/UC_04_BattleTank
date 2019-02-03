// RebusStudios 2019

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMover = CreateDefaultSubobject<UProjectileMovementComponent>(FName("MovementComponent"));
	if (ProjectileMover)
	{
		ProjectileMover->SetAutoActivate(false);
	}
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMover->SetVelocityInLocalSpace(FVector::ForwardVector*Speed);
	ProjectileMover->Activate(true);
	UE_LOG(LogTemp, Warning, TEXT("Projectile Launch @%f cmps"), Speed);
}