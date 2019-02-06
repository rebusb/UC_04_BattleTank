// RebusStudios 2019

#include "TankTrack.h"

#include "Engine/World.h"

void UTankTrack::SetThrottle(float Throttle)
{

	if (!this)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTankTrack this null!!!!!"));

		return;
	}

	auto TestCast = Cast<USceneComponent>(this);
	if (!TestCast)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Cast to USceneComponent failed!!"), *this->GetClass()->GetName());
		return;
	}
	FVector ForwardVec = this->GetForwardVector();

	if (Throttle!=0.0)
	{
		auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
		auto ForceLocation = GetComponentLocation();
		//auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

		auto OwningActor = GetOwner();
		if (OwningActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Track OwningActor:%s"), *OwningActor->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Track has no owner!"));
			return;
		}

		UE_LOG(LogTemp, Warning, TEXT("SetThrottle to %f, ForceApplied %s, ForceLocation %s"), Throttle, *ForceApplied.ToString(),*ForceLocation.ToString());

		auto TankRoot = Cast<UPrimitiveComponent>(OwningActor->GetRootComponent());

		if (TankRoot)
		{
			UE_LOG(LogTemp, Warning, TEXT("TankRoot component found"));
			TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Unable to get TankRoot component!!!!"));
		}
	}


}



