// RebusStudios 2019

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::InitializeTreads(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	TreadLeft = LeftTrackToSet;
	TreadLeft = RightTrackToSet;


}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	
	if (!TreadLeft||!TreadLeft) { return; }
	TreadLeft->SetThrottle(Throw);
	TreadRight->SetThrottle(Throw);
	//TODO tame double transform
}

void UTankMovementComponent::IntendTurn(float Throw)
{
	
	if (!TreadLeft||!TreadLeft) { return; }
	TreadLeft->SetThrottle(Throw);
	TreadRight->SetThrottle(-Throw);

}
