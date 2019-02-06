// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TankPlayerController.generated.h" // generated.h must always be last header included

class ATank;

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
	
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000; //10km in cm
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AimSystemSettings)
		FVector AimStartOffset;		//adjust aim trace origin, offset from root location in cm
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AimSystemSettings)
		float CrosshairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AimSystemSettings)
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
	bool GetSightRayHitLocation(OUT FVector& HitLocation) const;
};
