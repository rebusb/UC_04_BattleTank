// RebusStudios 2019

#include "TankTrack.h"

#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.bCanEverTick = true;
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	//UE_LOG(LogTemp, Warning, TEXT("%s CurrentThrottle:%f ForceApplied:%s"), *GetOwner()->GetName(),CurrentThrottle, *ForceApplied.ToString());
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.0, 1.0);
}


void UTankTrack::ApplySidewaysForce(float DeltaTime)
{
	// Correct for low friction physics slipping
	//Get slippage
	FVector BaseVector = GetRightVector();
	FVector Velocity = GetComponentVelocity();
	float Slippage = FVector::DotProduct(BaseVector, Velocity);
	float Speed = Velocity.Size();

	//UE_LOG(LogTemp, Warning, TEXT("Slippage: %f vs Speed: %f"), Slippage, Speed);

	//calc compensating force
	auto CorrectionAcceleration = -(Slippage / DeltaTime * BaseVector);

	//apply force (per tread!) to tank (root)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration)/2.0; // averaged across two tracks
	TankRoot->AddForce(CorrectionForce);
}

//Component OnHit() event delegate implementation
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	ApplySidewaysForce(DeltaTime);
	CurrentThrottle = 0.0;
}


