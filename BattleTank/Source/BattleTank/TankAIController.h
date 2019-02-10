// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "TankAIController.generated.h"


/**
 * Pathfinding movement calls and aiming toward player control
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	//radius AI stops moving toward player
	float AcceptanceRadius = 3000.0;	
	
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

};
