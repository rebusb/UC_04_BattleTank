// Fill out your copyright notice in the Description page of Project Settings.



#include "TankPlayerController.h"
#include "BattleTank.h"


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
	UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController %s BeginPlay()"), *(GetName()));

	AimStartOffset.Set(0.0, 0.0, 0.0);

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
		UE_LOG(LogTemp, Warning, TEXT("Hit Location %s "), *HitLocation.ToString());
		// TODO tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("LineTrace hit nothing."));
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{ 	// Get world location of linetrace through crosshair

	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation((float(ViewportSizeX) * CrosshairXLocation), (float(ViewportSizeY) * CrosshairYLocation));

	// Deproject the screen position of the crosshair to a world direction  !is factored in lesson code
	FVector WorldDirection, WorldLocation;
	bool result = DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection);
	if (!result) { return false; }

	//GetLookVectorHitLocation() this is factored function in lesson code, keeping it here for now
	// Line-trace along that look direction and see what we hit (up to max range)
	FHitResult OutHit;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	//UE_LOG(LogTemp, Warning, TEXT("World view location %s "), *WorldLocation.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("World view direction %s "), *WorldDirection.ToString());

	//debug line
	//FColor lineColor(1.0, 0.4, 0.0);
	//DrawDebugLine(GetWorld(), WorldLocation+FVector(0.0,10.0,0.0), (WorldLocation + WorldDirection * LineTraceRange), lineColor, true, 1.0, 1.0, 5.0);
	const FName Tag = TEXT("TraceTag"); //////   much nicer debug trace!!!
	GetWorld()->DebugDrawTraceTag = Tag; /////
	FCollisionQueryParams Params(Tag);//////

	 result = GetWorld()->LineTraceSingleByChannel(
		OutHit,
		WorldLocation,
		(WorldLocation + WorldDirection * LineTraceRange), 
		(ECollisionChannel::ECC_Visibility),
		Params
		);

	 if (!result) { return false; }


		 //HitLocation = (WorldLocation + WorldDirection * OutHit.Distance);
		// UE_LOG(LogTemp, Warning, TEXT("Hit Location distance scale direction %s "), *HitLocation.ToString());
		 HitLocation = OutHit.Location;

		//UE_LOG(LogTemp, Warning, TEXT("Screen location %s pixels"), *ScreenLocation.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("Viewport size %d,%d pixels"), ViewportSizeX, ViewportSizeY);
		



		return true;
	
	
	
	//if hit (landscape, enemy?)
		//set HitLocation to ws location of hit
		//return true
	//else
	return false;


}



