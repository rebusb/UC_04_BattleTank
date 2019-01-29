// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"




//#include "BattleTank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankAIController %s BeginPlay()"),*(GetName()));
	const ATank *Temp = GetControlledTank();
}


ATank* ATankAIController::GetControlledTank() const
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
