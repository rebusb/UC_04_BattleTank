// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;




UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	//UFUNCTION(BlueprintCallable, Category = "Firing Setup")	// X
	//	void SetBarrelReference(UTankBarrel* BarrelToSet);

	//UFUNCTION(BlueprintCallable, Category = "Firing Setup") //X
	//	void SetTurretReference(UTankTurret* TurretToSet);

	//deletgate aiming to AimingComponent
	void AimAt(FVector HitLocation);	

	//delegate Fire to AimingComponent
	UFUNCTION(BlueprintCallable)
		void Fire();	

protected:
	//// Aiming Component delegate 
	//UPROPERTY(BlueprintReadOnly)
	//UTankAimingComponent* TankAimingComponent = nullptr; //X

	//UPROPERTY(EditDefaultsOnly, Category = "Firing")
	//	float LaunchSpeed = 10000.0; // cm/s // X

	//UPROPERTY(EditDefaultsOnly, Category = "Firing")
	//	float ReloadTimeInSeconds = 3.0; // X

	//Aiming Component for accessing aiming and firing systems
	UPROPERTY(BlueprintReadOnly, Category = "FiringSystem")
		UTankAimingComponent* AimingComponent = nullptr;  //TODO check priviledges for this

private:
	// Sets default values for this pawn's properties
	ATank();



	////Local reference to the barrel for launching projectile from
	//UTankBarrel* Barrel; //X

	//// used to keep track of reload time
	//float LastFireTime = 0.0; //X
 //

	////reference to projectile
	//UPROPERTY(EditDefaultsOnly, Category = "Setup")
	//	TSubclassOf<AProjectile> ProjectileBP;   // lets try to keep this on tank? let tank decide projectile to launch...

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
