// RebusStudios 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"

#include "TankBarrel.generated.h"


/**
 * Control Barrel movement (Elevate)
 */

//UTankBarrel Control barrel elevation on tank
UCLASS(ClassGroup = (TankParts), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);
	
private:
	//maximum movement speed of barrel elevator
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDegressPerSecond = 8.0;

	//maximum angle barrel can rotate
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxBarrelAngle = 50.0;

	//minimum angle barrel can rotate
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MinBarrelAngle = -3.0;


};
