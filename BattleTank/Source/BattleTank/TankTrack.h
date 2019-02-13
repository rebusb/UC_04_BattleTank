// RebusStudios 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set limits and apply driving force to tank (treads)
 */
UCLASS(ClassGroup=(TankParts), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//initializer to set tick true
	UTankTrack();
	
		//Max Driving Force (N)
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		float TrackMaxDrivingForce = 40000000; // kg m / s*s  - may have to be cm

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float SetInput);

	virtual void BeginPlay() override;

	void DriveTrack();

	void ApplySidewaysForce(float DeltaTime);

private:
	float CurrentThrottle = 0.0;

	//Component OnHit() event delegate declared
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
