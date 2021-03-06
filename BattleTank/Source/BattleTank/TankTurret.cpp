// RebusStudios 2019

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::Spin(float SpinRate)
{
	//+1 max up speed, -1 max down speed
	float RotationChange = FMath::Clamp<float>(SpinRate, -1.0, 1.0) * MaxDegressPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewRotation = RelativeRotation.Yaw + RotationChange;
	//call parent class method to rotate
	SetRelativeRotation(FRotator(0.0,NewRotation,0.0));
}

