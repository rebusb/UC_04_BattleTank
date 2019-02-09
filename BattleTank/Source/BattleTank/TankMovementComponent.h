// RebusStudios 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Component to delegate tank movement input controls
 */
UCLASS(ClassGroup = (TankParts), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendTurn(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void InitializeTreads(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);
	
private:
	UTankTrack* TreadRight = nullptr;
	UTankTrack* TreadLeft = nullptr;

	//override NavMovementComp' method
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

};
