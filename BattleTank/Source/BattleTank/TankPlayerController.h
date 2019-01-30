// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Tank.h"

#include "TankPlayerController.generated.h" // generated.h must always be last header included

/**
 *
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// flag to check if tick() has fired to prevent log spamming
	bool bHasTicked;
	bool bHasPlayerTicked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScreenAimingPosition)
		float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScreenAimingPosition)
		float CrosshairYLocation = 0.33333;


public:
	ATankPlayerController(const FObjectInitializer& ObjectInitializer);

	ATank* GetControlledTank() const;

	void BeginPlay() override;

	void Tick(float DeltaTime) override;
	//	void PlayerTick(float DeltaTime) override;

private:

	//Start moving barrel toward aim crosshair
	void AimTowardsCrosshair();

	//Set OUT parameter to world location of aim sight hit, return true if hit
	bool GetSightRayHitLocation(FVector& HitLocation) const;

};
