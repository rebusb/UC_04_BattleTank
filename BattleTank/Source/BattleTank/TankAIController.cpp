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
	// TODO Move toward target

	// Attack target
	AttackPlayer();
	//Target is enemy player
	
}

void ATankAIController::AttackPlayer()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	auto Target = Cast<ATank>(PlayerController->GetPawn());
	auto Tank = Cast<ATank>(GetPawn());
	if(Tank&&Target)
	{
		// Aim toward target
		FVector HitLocation = Target->GetTargetLocation();
		Tank->AimAt(HitLocation);
		Tank->Fire();
		// Fire when ready
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Unable to AttackPlayer"));
	}

}