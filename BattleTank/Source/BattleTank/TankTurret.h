// RebusStudios 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (TankParts), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	//turn turret 1.0 rotates clockwise, -1.0 anticlockwise
	void Spin(float SpinRate);

private:
	//maximum movement speed of turret rotation
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDegressPerSecond = 30.0;

	
	
};
