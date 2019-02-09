// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "Tank.h"
#include "Engine/World.h"



//#include "BattleTank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankAIController %s BeginPlay()"),*(GetName()));

}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ThisTank attacks PlayerTank
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	auto PlayerTank = Cast<ATank>(PlayerController->GetPawn());
	auto ThisTank = Cast<ATank>(GetPawn());
	if ensure(ThisTank&&PlayerTank)
	{
		//Move toward target
		MoveToActor(PlayerTank, AcceptanceRadius);	//TODO check close enough radius

		// Aim toward target and fire
		FVector HitLocation = PlayerTank->GetTargetLocation();

		//refac - how do we get these commands from AimComponent--- need to get aim component ref...
		ThisTank->AimAt(HitLocation);
		ThisTank->Fire();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Unable to AttackPlayer"));
	}
}

