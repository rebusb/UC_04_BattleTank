// RebusStudios 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(TankParts), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//set reference to TankBarrel component, sent from tank BP
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	//set reference to TankTurret component, sent from tank BP
	void SetTurretReference(UTankTurret* TurretToSet);

	//TODO Add set turret reference

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation, float LaunchSpeed);

	//Bring Tank barrel in line with aim direction
	void MoveBarrelTowards(FVector AimDirection);
		
private:
	UTankBarrel* BarrelComponent = nullptr;
	UTankTurret* TurretComponent = nullptr;

};
