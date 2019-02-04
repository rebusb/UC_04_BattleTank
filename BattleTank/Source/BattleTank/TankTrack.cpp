// RebusStudios 2019

#include "TankTrack.h"

#include "Engine/World.h"

void UTankTrack::SetThrottle(float Throttle)
{
	if (Throttle!=0.0)
	{
		auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
		auto ForceLocation = GetComponentLocation();
		auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
		TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	}
}



