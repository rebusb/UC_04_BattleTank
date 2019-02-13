// RebusStudios 2019

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/World.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
		LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	if (ensure(ImpactBlast))
	{
		ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		ImpactBlast->SetAutoActivate(false);
	}

	ProjectileMover = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	if ensure(ProjectileMover)
	{
		ProjectileMover->SetAutoActivate(false);
	}

	BlastForce = CreateDefaultSubobject<URadialForceComponent>(FName("Blast Force"));
	BlastForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	//CollisionMesh registers OnHit() delegate
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}


void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMover->SetVelocityInLocalSpace(FVector::ForwardVector*Speed);
	ProjectileMover->Activate(true);
}

//Component OnHit() event delegate implementation
void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// on hit deactivate launch fx
	LaunchBlast->DeactivateSystem();
	// activate impact fx
	ImpactBlast->ActivateSystem();
	// send blast force
	BlastForce->FireImpulse();

}