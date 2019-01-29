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

	if (!bHasTicked)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController has ticked."));
		bHasTicked = true;
	}
}



ATank* ATankPlayerController::GetControlledTank() const
{

	ATank* TankPawn = Cast<ATank>(GetPawn());
	if (TankPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Got Tank Pawn %s"), *TankPawn->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Did NOT get Tank Pawn !!!"));
	}
	return TankPawn;

}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) {return;}
	
	// Get world location of linetrace through crosshair
	// if it gets hit (landscape, enemy?) 
		// tell controlled tank to aim at this point
}



