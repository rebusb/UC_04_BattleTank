// RebusStudios 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UENUM() enum class EFiringState : uint8
{
	Reloading	UMETA(DisplayName="Reloading"),
	Aiming	UMETA(DisplayName = "Aiming"),
	Locked	UMETA(DisplayName = "Locked"),
	Empty UMETA(DisplayName = "Empty"),
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

	UFUNCTION(BlueprintCallable, Category = "FiringSystem")
		int GetAmmoCount() const;

protected:
	//Aim and Firing system settings
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float LaunchSpeed = 10000.0; // cm/s

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float ReloadTimeInSeconds = 3.0; 

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 InitialAmmoCount = 5; 
		


	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	//getter for looking up FiringState
	UFUNCTION(BlueprintCallable, Category = "FiringSystem")
	EFiringState GetFiringState() const;

	//Bring Tank barrel in line with aim direction
	void MoveBarrelTowards(FVector AimDirection);
		
private:
	UTankBarrel* BarrelComponent = nullptr;
	UTankTurret* TurretComponent = nullptr;

	int32 AmmoCount = 0;
	// Tank firing status
	
	EFiringState FiringState = EFiringState::Reloading;

	//reference to projectile
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBP;   

	//track firing system reload
	float LastFireTime = 0.0;

	//hold current aim direction
	FVector AimDirection=FVector(0.0);

	//Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	//Check current Barrel forward vector against AimDirection, true if Equals()
	bool IsBarrelMoving();


};
