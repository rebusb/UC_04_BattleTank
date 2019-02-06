// RebusStudios 2019

#include "TankMovementComponent.h"
#include "BattleTank.h"
#include "TankTrack.h"


void UTankMovementComponent::InitializeTreads(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet)
	{
		UE_LOG(LogTemp, Error, TEXT("TankMovementComponent unable to InitializeTreads!!!"));
		return;
	}

	TreadLeft = LeftTrackToSet;
	TreadLeft = RightTrackToSet;

}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	
	if (!TreadLeft||!TreadLeft) { 
		UE_LOG(LogTemp, Warning, TEXT("Error in IntendMoveForward"));
		return;
	}
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
