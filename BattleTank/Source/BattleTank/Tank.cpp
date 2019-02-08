// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

#include "Engine/World.h"

// Sets default values
ATank::ATank()
{	
	UE_LOG(LogTemp, Warning, TEXT("Tank in constructor"));
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}



// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	//get AimingComponent
	AimingComponent = FindComponentByClass<UTankAimingComponent>();
	if (!AimingComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Tank unable to find AimingComponent!!!"));
	}
}

void ATank::AimAt(FVector HitLocation) {

	if (!AimingComponent) { return; }
	AimingComponent->AimAt(HitLocation);

}

void ATank::Fire() {

	if (!AimingComponent) { return; }
	AimingComponent->Fire();

}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

