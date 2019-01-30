// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "BattleTank.h"
#include "GameFramework/GameMode.h"

//experiment to see if can kill tick...
ATankPlayerController::ATankPlayerController(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	//setting this to false does kill the tick()
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController %s BeginPlay()"), *(GetName()));

	bHasTicked = false; 
	bHasPlayerTicked = false;

	SetActorTickEnabled(true);

	const ATank *Temp = GetControlledTank();
}


//void ATankPlayerController::PlayerTick(float DeltaTime)
//{
//
//	Super::PlayerTick(DeltaTime);
//
//	if (!bHasPlayerTicked)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController has PlayerTicked()."));
//		bHasPlayerTicked = true;
//	}
//
//}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();

	if (!bHasTicked)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController has ticked."));
		bHasTicked = true;
	}

	
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
		// TODO tell controlled tank to aim at this point
		// UE_LOG(LogTemp, Warning, TEXT("Look Location: %s"), *HitLocation.ToString());
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{ 	// Get world location of linetrace through crosshair

	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation((float(ViewportSizeX) * CrosshairXLocation), (float(ViewportSizeY) * CrosshairYLocation));

	// Deproject the screen position of the crosshair to a world direction
	FVector WorldDirection, WorldLocation;
	bool result = DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection);
	if (!result) { return false; }


	if (!bHasTicked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Screen location %s pixels"), *ScreenLocation.ToString());
		UE_LOG(LogTemp, Warning, TEXT("Viewport size %d,%d pixels"), ViewportSizeX, ViewportSizeY);
		UE_LOG(LogTemp, Warning, TEXT("World view location %s "), *WorldLocation.ToString());
		UE_LOG(LogTemp, Warning, TEXT("World view direction %s "), *WorldDirection.ToString());

	}
	
	// Line-trace along that look direction and see what we hit (up to max range)
	
	//if hit (landscape, enemy?)
		//set HitLocation to ws location of hit
		//return true
	//else
	return false;


}



