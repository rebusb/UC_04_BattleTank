// RebusStudios 2019

#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	//+1 max up speed, -1 max down speed
	auto ElevationChange = FMath::Clamp<float>(RelativeSpeed,-1.0,1.0) * MaxDegressPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	//call parent class method to rotate
	SetRelativeRotation(FRotator(FMath::Clamp<float>(RawNewElevation, MinBarrelAngle,MaxBarrelAngle), 0.0, 0.0));

}

