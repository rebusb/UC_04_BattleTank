// RebusStudios 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"


class ASprungWheel;

/**
 * TankTrack is used to set limits and apply driving force to tank (treads)
 */
UCLASS(ClassGroup=(TankParts), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//initializer to set tick true
	UTankTrack();
	
		//Max Driving Force (N)
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		float TrackMaxDrivingForce = 40000000; // kg m / s*s  - may have to be cm

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float SetInput);


	void DriveTrack(float CurrentTrottle);


private:
	float CurrentThrottle = 0.0;

	//get const array of this track's attached wheels
	TArray<class ASprungWheel*> GetWheels() const;

};
