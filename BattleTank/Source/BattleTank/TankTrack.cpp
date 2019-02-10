// RebusStudios 2019

#include "TankTrack.h"

#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("KITTY: UTankTrack init"));
}

void UTankTrack::OnRegister()
{
	Super::OnRegister();
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankTrack::SetThrottle(float Throttle)
{

	if (Throttle!=0.0)
	{

		FVector ForwardVec = this->GetForwardVector();


		auto ForceApplied = ForwardVec * Throttle * TrackMaxDrivingForce;
		auto ForceLocation = GetComponentLocation();
		auto OwningActor = GetOwner();

		if (!ensure(OwningActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("Track has no owner!"));
			return;
		}

		//UE_LOG(LogTemp, Warning, TEXT("SetThrottle to %f, ForceApplied %s, ForceLocation %s"), Throttle, *ForceApplied.ToString(),*ForceLocation.ToString());

		auto TankRoot = Cast<UPrimitiveComponent>(OwningActor->GetRootComponent());

		if ensure(TankRoot)
		{
			TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Unable to get TankRoot component!!!!"));
		}
	}


}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Correct for low friction physics slipping
	//Get slippage
	FVector BaseVector = GetRightVector();
	FVector Velocity = GetComponentVelocity();
	float Slippage = FVector::DotProduct(BaseVector,Velocity);
	float Speed = Velocity.Size();
	
	UE_LOG(LogTemp, Warning, TEXT("Slippage: %f vs Speed: %f"), Slippage, Speed);

	//calc compensating force
	auto CorrectionAcceleration = -(Slippage / DeltaTime * BaseVector);

	//apply force (per tread!) to tank (root)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration)/2.0; // averaged across two tracks
	TankRoot->AddForce(CorrectionForce);
}





