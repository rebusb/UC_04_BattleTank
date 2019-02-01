// RebusStudios 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"

#include "TankBarrel.generated.h"


/**
 * 
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
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegressPerSecond = 20;

	//maximum angle barrel can rotate
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxBarrelAngle = 50.0;

	//minimum angle barrel can rotate
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinBarrelAngle = -3.0;

};
