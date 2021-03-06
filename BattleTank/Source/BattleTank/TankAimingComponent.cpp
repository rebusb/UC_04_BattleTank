// RebusStudios 2019

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"




// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

void UTankAimingComponent::InitializeAimingComponent(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if(!ensure(BarrelToSet&&TurretToSet)) 
	{
		UE_LOG(LogTemp, Error, TEXT("InitializeAimingComponent unable to InitializeAimingComponent"));
		return;
	}

	BarrelComponent = BarrelToSet;
	TurretComponent = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	//set inital LastFireTime so we are loading on start
	LastFireTime = GetWorld()->GetTimeSeconds();
	AmmoCount = InitialAmmoCount;
	FiringState = EFiringState::Reloading;
	
}


void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (FiringState != EFiringState::Empty) //TODO pick up ammo when empty?S
	{
		if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
		{
			FiringState = EFiringState::Reloading;
		}
		else
		{
			if (IsBarrelMoving())
			{
				FiringState = EFiringState::Aiming;
			}
			else
			{
				FiringState = EFiringState::Locked;
			}
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("FiringState:%i"),FiringState);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	float Tolerance = 0.001;
	if (!ensure(BarrelComponent)) { return false; }
	auto BarrelVector = BarrelComponent->GetForwardVector().GetSafeNormal();
	FVector VDiff = BarrelVector - AimDirection;

	if (BarrelVector.Equals(AimDirection,Tolerance))
	{
		return false;	
	}
	else
	{
		return true;
	}
}

///AimAt called by Controller classes to move turret&barrel into firing position given target point in world
void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(BarrelComponent)) { return; }

	// get vector to launch shell, TODO: consider toggle high low as part of advanced game (ex. shot over mtns)
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

	if (result)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
	} 

	MoveBarrelTowards(AimDirection);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(ProjectileBP)) { return; }

	if (FiringState!=EFiringState::Empty&&FiringState!=EFiringState::Reloading) {
		if (!ensure(BarrelComponent)) { return; }
		// spawn projectile at end of barrel (muzzle socket)
	
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBP,
				BarrelComponent->GetSocketLocation(FName("muzzle")),
				BarrelComponent->GetSocketRotation(FName("muzzle"))
				);
			// TODO: May need to tell Projectile to ignore Barrel collision somehow
			if (!ensure(Projectile)) { return; }
			Projectile->LaunchProjectile(LaunchSpeed);
			//reset fire time
			LastFireTime = GetWorld()->GetTimeSeconds();
			AmmoCount--;
	
		if(AmmoCount<=0)
		{
			FiringState = EFiringState::Empty;
		}
	}
}

int32 UTankAimingComponent::GetAmmoCount() const
{
	return AmmoCount;
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
	float Spin = DeltaRotator.Yaw;
	/*if(Spin<-180.0)
	{
		Spin += 360.0;
	}
	if (Spin>180.0)
	{
		Spin -= 360.0;
	}
	UE_LOG(LogTemp, Warning, TEXT("Turret given Yaw %f spin to %f"),DeltaRotator.Yaw, Spin);*/
	// so spin to amount... if abs(spin)>180 
	if(FMath::Abs(Spin)>180)
	{
		TurretComponent->Spin(-Spin);
	}
	else
	{
		TurretComponent->Spin(Spin);
	}

	//rotate to elevation
	BarrelComponent->Elevate(DeltaRotator.Pitch);	

}

FString UTankAimingComponent::GetAmmoAsString()
{
	
	FString AmmoString = FString();
	for (int i = 0;i<AmmoCount;i++) {
		AmmoString += ".";
	}
	return AmmoString;
}
