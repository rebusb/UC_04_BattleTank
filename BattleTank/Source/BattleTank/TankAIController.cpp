// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

//#include "BattleTank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ThisTank attacks PlayerTank
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	auto PlayerPawn = PlayerController->GetPawn();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if ensure(AimingComponent&&PlayerPawn)
	{
		//Move toward target
		MoveToActor(PlayerPawn, AcceptanceRadius);	//TODO check close enough radius

		// Aim toward target and fire
		FVector HitLocation = PlayerPawn->GetTargetLocation();

		//refac - how do we get these commands from AimComponent--- need to get aim component ref...
		AimingComponent->AimAt(HitLocation);
		AimingComponent->Fire();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s missing ThisTank or PlayerTank"));
	}
}

