// RebusStudios 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TankPlayerController.generated.h" // generated.h must always be last header included

class ATank;
class UTankAimingComponent;

/**
 *  Handles Player Aim (and...?)
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:	
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000; //10km in cm
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AimSystem")
		FVector AimStartOffset;		//adjust aim trace origin, offset from root location in cm
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AimSystem")
		float CrosshairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AimSystem")
		float CrosshairYLocation = 0.33333;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);

public:
	ATankPlayerController(const FObjectInitializer& ObjectInitializer);

	//Make controlled tank available to blueprints
	UFUNCTION(BlueprintCallable, Category = "Setup")
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
