// RebusStudios 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// using projectile movement comp' send projectile flying
	void LaunchProjectile(const float LaunchSpeed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*UPROPERTY(EditAnywhere, Category="Setup")
	float ProjectileSpeed = 5000.0;*/

private:
	// damage system TODO different damages for different class tanks
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float ProjectileDamage = 5.0;

	// our registered components
	UProjectileMovementComponent* ProjectileMover = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* LaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* ImpactBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		URadialForceComponent* BlastForce = nullptr;
	//Timer properties
	FTimerHandle SelfDestructTimer;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float SelfDestructDelay = 2.0;

	//Component OnHit() event delegate declared
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	//Called by timer delay after impact
	UFUNCTION()
		void SelfDestruct();
};
