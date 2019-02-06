// RebusStudios 2019

#include "TankTrack.h"

#include "Engine/World.h"

void UTankTrack::SetThrottle(float Throttle)
{

	if (Throttle!=0.0)
	{
		auto TestCast = Cast<USceneComponent>(this);
		if (!TestCast)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s Cast to USceneComponent failed!!"), *this->GetClass()->GetName());
			return;
		}
		FVector ForwardVec = this->GetForwardVector();


		auto ForceApplied = ForwardVec * Throttle * TrackMaxDrivingForce;
		auto ForceLocation = GetComponentLocation();
		auto OwningActor = GetOwner();

		if (!OwningActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Track has no owner!"));
			return;
		}

		//UE_LOG(LogTemp, Warning, TEXT("SetThrottle to %f, ForceApplied %s, ForceLocation %s"), Throttle, *ForceApplied.ToString(),*ForceLocation.ToString());

		auto TankRoot = Cast<UPrimitiveComponent>(OwningActor->GetRootComponent());

		if (TankRoot)
		{
			TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Unable to get TankRoot component!!!!"));
		}
	}


}



