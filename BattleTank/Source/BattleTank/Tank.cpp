// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

#include "Engine/World.h"

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
	if (!Barrel) { return; }
	AProjectile* Temp = GetWorld()->SpawnActor<AProjectile>(ProjectileBP,Barrel->GetSocketLocation("muzzle"), Barrel->GetSocketRotation("muzzle"));

	//May need to tell Projectile to ignore Barrel collision somehow
	if (Temp)
	{
		//Projectile = Temp;
		UE_LOG(LogTemp, Warning, TEXT("%f: Tank %s Fire!!! Projectile==%s"), GetWorld()->GetTimeSeconds(), *GetName(), *Temp->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%f: Tank %s unable to spawn Projectile"), *GetName());
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
	Fire();
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

