// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ATank::ATank()
{	
	UE_LOG(LogTemp, Warning, TEXT("Tank in constructor"));
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>("AimingComponent");

}


void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;
	if (Barrel && bIsReloaded) {
		//reset fire time
		LastFireTime = GetWorld()->GetTimeSeconds();

		// spawn projectile at end of barrel (muzzle socket)
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBP,
			Barrel->GetSocketLocation(FName("muzzle")),
			Barrel->GetSocketRotation(FName("muzzle"))
			);

		//May need to tell Projectile to ignore Barrel collision somehow
		if (Projectile)
		{
			Projectile->LaunchProjectile(LaunchSpeed);
			//UE_LOG(LogTemp, Warning, TEXT("%f: Tank %s Fire!!! Projectile==%s"), GetWorld()->GetTimeSeconds(), *GetName(), *Projectile->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%f: Tank %s unable to spawn Projectile"), *GetName());
		}
	}
}


//AimAt called to target world location
void ATank::AimAt(FVector HitLocation)
{

	TankAimingComponent->AimAt(HitLocation,LaunchSpeed);

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = 0;



}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

