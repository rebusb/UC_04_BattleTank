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

public:
	
protected:
	//radius AI stops moving toward player
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float AcceptanceRadius = 5000.0;	

private:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

};
