// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "BattleTank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController BeginPlay()"));
	const ATank *Temp = GetControlledTank();
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




