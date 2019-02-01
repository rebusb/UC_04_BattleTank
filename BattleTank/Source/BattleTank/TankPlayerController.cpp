// Fill out your copyright notice in the Description page of Project Settings.



#include "TankPlayerController.h"
#include "BattleTank.h"

#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/GameMode.h"
#include "DrawDebugHelpers.h"


//experiment to see if can kill tick...
ATankPlayerController::ATankPlayerController(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	//setting this to false does kill the tick()
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AimStartOffset.Set(0.0, 0.0, 0.0);

	bHasTicked = false; 
	bHasPlayerTicked = false;

	SetActorTickEnabled(true);

	const ATank *Temp = GetControlledTank();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();

}

ATank* ATankPlayerController::GetControlledTank() const
{

	ATank* TankPawn = Cast<ATank>(GetPawn());

	return TankPawn;

}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) {return;}
	
	FVector HitLocation; // Out parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		//  tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
	}
	else
	{
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& HitLocation) const
{ 	// Get world location of linetrace through crosshair

	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation((float(ViewportSizeX) * CrosshairXLocation), (float(ViewportSizeY) * CrosshairYLocation));

	// Deproject the screen position of the crosshair to a world direction  !is factored into separate function in lesson code
	FVector WorldDirection, WorldLocation;
	bool result = DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection);
	if (!result) { return false; }

	//GetLookVectorHitLocation() this is factored function in lesson code, keeping it here for now
	// Line-trace along that look direction and see what we hit (up to max range)
	FHitResult OutHit;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	result = GetWorld()->LineTraceSingleByChannel(
		OutHit,
		WorldLocation,
		(WorldLocation + WorldDirection * LineTraceRange), 
		(ECollisionChannel::ECC_Visibility)
		);

	if (!result) { return false; }

    HitLocation = OutHit.Location;

    return true;

}



