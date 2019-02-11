// RebusStudios 2019

#include "TankMovementComponent.h"
#include "BattleTank.h"
#include "TankTrack.h"


void UTankMovementComponent::InitializeTreads(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) {return;}

	TreadLeft = LeftTrackToSet;
	TreadRight = RightTrackToSet;

}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	
	if (!ensure(TreadLeft&&TreadLeft)) {return;}
	TreadLeft->SetThrottle(Throw);
	TreadRight->SetThrottle(Throw);

}

void UTankMovementComponent::IntendTurn(float Throw)
{
	
	if (!ensure(TreadLeft&&TreadLeft)) {return;}
	TreadLeft->SetThrottle(Throw);
	TreadRight->SetThrottle(-Throw);

}

///AI will call this to direct tank (AI Path Finding System)
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	float RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurn(RightThrow);
	/*float Mag = Cross.Size();
	float TurnThrow = Mag * (abs(Cross.Z)/Cross.Z);
	

	float MyRotation = GetOwner()->GetActorRotation().Yaw;*/
}