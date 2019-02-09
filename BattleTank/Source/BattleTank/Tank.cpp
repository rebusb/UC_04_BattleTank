// RebusStudios 2019

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

#include "Engine/World.h"

// Sets default values
ATank::ATank()
{	
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("KITTY: %s in constructor"),*TankName);
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}



// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("KITTY: %s in BeginPlay CPP"), *TankName);

	//get AimingComponent
	AimingComponent = FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("Tank unable to find AimingComponent!!!"));
	}
}

void ATank::AimAt(FVector HitLocation) {

	if (!ensure(AimingComponent)) { return; }
	AimingComponent->AimAt(HitLocation);

}

void ATank::Fire() {

	//in Ben's code this is still implemented in Tank.cpp where I have it delegated
	if (!ensure(AimingComponent)) { return; }
	AimingComponent->Fire();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

