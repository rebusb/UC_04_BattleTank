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
	TreadRight = RightTrackToSet;

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

///AI will call this to direct tank (AI Path Finding System)
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto Name = GetOwner()->GetName();

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	float DirectionCosine = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(DirectionCosine);

	//UE_LOG(LogTemp, Warning, TEXT("%s given velocity %s"), *Name, *MoveVelocity.ToString());
}