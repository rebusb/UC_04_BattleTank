// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"



//#include "BattleTank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankAIController %s BeginPlay()"),*(GetName()));
	ATank *OurTank = GetControlledTank();
	ATank *PlayerTank = GetPlayerTank();

	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Got Player Tank %s"), *PlayerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Did NOT get Player Tank !!!"));
	}

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

ATank * ATankAIController::GetPlayerTank() const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) { return nullptr; }
	return  Cast<ATank>(PlayerController->GetPawn());
}
