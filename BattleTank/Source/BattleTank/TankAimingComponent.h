// RebusStudios 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UENUM() enum class EFiringStatus : uint8
{
	Reloading	UMETA(DisplayName="Reloading"),
	Aiming	UMETA(DisplayName = "Aiming"),
	Locked	UMETA(DisplayName = "Locked"),
	Unknown	UMETA(DisplayName = "Unknown")
};

UCLASS( ClassGroup=(TankParts), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category="Initialize")
	void InitializeAimingComponent(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category="FiringSystem")
		void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category="FiringSystem")
		void Fire();

protected:
	//Aim and Firing system settings
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float LaunchSpeed = 10000.0; // cm/s // X

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float ReloadTimeInSeconds = 3.0; // X


	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Tank firing status
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

	//Bring Tank barrel in line with aim direction
	void MoveBarrelTowards(FVector AimDirection);
		
private:
	UTankBarrel* BarrelComponent = nullptr;
	UTankTurret* TurretComponent = nullptr;

	//reference to projectile
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBP;   // lets try to keep this on tank? let tank decide projectile to launch...

	//track firing system reload
	float LastFireTime = 0.0;

	//hold current aim direction
	FVector AimDirection=FVector(0.0);

	//Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	//Check current Barrel forward vector against AimDirection, true if Equals()
	bool IsBarrelMoving();


};
