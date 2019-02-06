// RebusStudios 2019

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void  UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	BarrelComponent = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	TurretComponent = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!BarrelComponent) { return; }

	// get vector to launch shell, consider toggle high low as part of advanced game (ex. shot over mtns)
	// OUT for resulting launch velocity
	FVector OutLaunchVelocity(0.0);
	auto StartLocation = BarrelComponent->GetSocketLocation("muzzle");
	TArray<AActor*>ActorsToIgnore;
	ActorsToIgnore.Add(Cast<AActor>(this));
	bool DrawDebug = false;
	auto result = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false, //high arc?
		60.0, //shell radius
		0.0, //alter gravity
		ESuggestProjVelocityTraceOption::DoNotTrace,//traceOption,
		FCollisionResponseParams::DefaultResponseParam,
		ActorsToIgnore,
		DrawDebug
	);

	auto Time = GetWorld()->GetTimeSeconds();
	FVector AimDirection;

	if (result)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
	} 

	MoveBarrelTowards(AimDirection);
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Bring Tank barrel in line with aim direction
	//Get current barrel direction/rotation

	auto BarrelRotator = BarrelComponent->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	//rotate to azmuth
	// rotate turret component
	//convert yaw to spin direction... (or let Turret do that?)
	TurretComponent->Spin(DeltaRotator.Yaw);

	//rotate to elevation
	//UE_LOG(LogTemp, Warning, TEXT("Rotator.Pitch %f"), DeltaRotator.Pitch);
	BarrelComponent->Elevate(DeltaRotator.Pitch);	

}
