// RebusStudios 2019

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	if (ensure(CollisionMesh))
	{
		SetRootComponent(CollisionMesh);
		CollisionMesh->SetNotifyRigidBodyCollision(true);
		CollisionMesh->ToggleVisibility(true);
	}
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	if (ensure(LaunchBlast))
	{
		LaunchBlast->AttachTo(RootComponent);
	}


	ProjectileMover = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	if ensure(ProjectileMover)
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
}