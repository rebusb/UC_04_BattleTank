// RebusStudios 2019

#include "TankTrack.h"


void UTankTrack::SetThrottle(float SetInput)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s sets throttle to %f"), *Name, SetInput);

}


