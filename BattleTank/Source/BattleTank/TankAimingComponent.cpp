// RebusStudios 2019

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void  UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	BarrelComponent = BarrelToSet;
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
	bool DrawDebug = true;
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

	if (result)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to SuggestProjectileVelocity"));
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Bring Tank barrel in line with aim direction
	//Get current barrel direction/rotation

	auto BarrelRotator = BarrelComponent->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator %s"), *AimAsRotator.ToString());

	//Get delta to desired Aim (Aim-current)
	//Apply relative rotation to turret on Z axis to set aszmuth 
	//Apply relative rotation to barrel on X axis to set elevation

}

/*	UE_LOG(LogTemp, Warning, TEXT("%s aims at %s with launch vel %s"),
			*GetOwner()->GetName(),
			*HitLocation.ToString(),
			*AimDirection.ToString());
*/