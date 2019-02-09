// RebusStudios 2019

#include "TankMovementComponent.h"
#include "BattleTank.h"
#include "TankTrack.h"


void UTankMovementComponent::InitializeTreads(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	UE_LOG(LogTemp, Warning, TEXT("KITTY: TankMovementComponent in InitTreads"));

	if (!ensure(LeftTrackToSet && RightTrackToSet))
	{
		UE_LOG(LogTemp, Error, TEXT("TankMovementComponent unable to InitializeTreads!!!"));
		return;
	}

	TreadLeft = LeftTrackToSet;
	TreadRight = RightTrackToSet;

}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	
	if (!ensure(TreadLeft&&TreadLeft)) { 
		UE_LOG(LogTemp, Warning, TEXT("Error in IntendMoveForward"));
		return;
	}
	TreadLeft->SetThrottle(Throw);
	TreadRight->SetThrottle(Throw);
	//TODO tame double transform
}

void UTankMovementComponent::IntendTurn(float Throw)
{
	
	if (!ensure(TreadLeft&&TreadLeft)) {
		UE_LOG(LogTemp, Warning, TEXT("Error in IntendTurn"));
		return; return; }
	TreadLeft->SetThrottle(Throw);
	TreadRight->SetThrottle(-Throw);

}

///AI will call this to direct tank (AI Path Finding System)
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto Name = GetOwner()->GetName();

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	
	IntendMoveForward(ForwardThrow);

	FVector Cross = FVector::CrossProduct(TankForward, AIForwardIntention);
	float Mag = Cross.Size();
	float TurnThrow = Mag * (abs(Cross.Z)/Cross.Z);
	IntendTurn(TurnThrow);

	float MyRotation = GetOwner()->GetActorRotation().Yaw;
	//UE_LOG(LogTemp, Warning, TEXT("%s Turns %f, Yaw %f"), *Name, TurnThrow,MyRotation);
}