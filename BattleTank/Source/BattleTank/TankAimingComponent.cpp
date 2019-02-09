// RebusStudios 2019

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("KITTY: TankAimingComp in constructor"));
}


void UTankAimingComponent::InitializeAimingComponent(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if(!ensure(BarrelToSet&&TurretToSet)) 
	{
		UE_LOG(LogTemp, Error, TEXT("InitializeAimingComponent unable to InitializeAimingComponent"));
		return;
	}

	BarrelComponent = BarrelToSet;
	TurretComponent = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("KITTY: TankAimingComp in BeginPlay"));

	//set inital LastFireTime so we are loaded on start
	LastFireTime = GetWorld()->GetTimeSeconds();
	
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(BarrelComponent)) { return; }

	// get vector to launch shell, consider toggle high low as part of advanced game (ex. shot over mtns)
	// OUT for resulting launch velocity
	FVector OutLaunchVelocity(0.0);
	auto StartLocation = BarrelComponent->GetSocketLocation("muzzle");
	TArray<AActor*>ActorsToIgnore;
	ActorsToIgnore.Add(Cast<AActor>(this));
	bool DrawDebug = false;
	auto result = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false, //high arc?
		60.0, //shell radius
		0.0, //alter gravity
		ESuggestProjVelocityTraceOption::DoNotTrace,//traceOption,
		FCollisionResponseParams::DefaultResponseParam,
		ActorsToIgnore,
		DrawDebug
	);

	auto Time = GetWorld()->GetTimeSeconds();
	FVector AimDirection;

	if (result)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
	} 

	MoveBarrelTowards(AimDirection);
}

void UTankAimingComponent::Fire()
{
	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;
	if (ensure(BarrelComponent) && bIsReloaded) {
		//reset fire time
		LastFireTime = GetWorld()->GetTimeSeconds();

		// spawn projectile at end of barrel (muzzle socket)
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBP,
			BarrelComponent->GetSocketLocation(FName("muzzle")),
			BarrelComponent->GetSocketRotation(FName("muzzle"))
			);

		//May need to tell Projectile to ignore Barrel collision somehow
		if ensure(Projectile)
		{
			Projectile->LaunchProjectile(LaunchSpeed);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%f: AImComponent %s unable to spawn Projectile"), *GetName());
		}
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Bring Tank barrel in line with aim direction
	//Get current barrel direction/rotation

	auto BarrelRotator = BarrelComponent->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	//rotate to azmuth
	// rotate turret component
	TurretComponent->Spin(DeltaRotator.Yaw);

	//rotate to elevation
	BarrelComponent->Elevate(DeltaRotator.Pitch);	

}
