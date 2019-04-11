// RebusStudios 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Setup")
		float SpringStrength = 1000;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float SpringDamp = 100;

	UFUNCTION()
		void AddDrivingForce(float ForceMagnitude);

	//UPROPERTY(EditAnywhere, Category = "Setup")
	//	float BaseMass = 10;

	//UPROPERTY(EditAnywhere, Category = "Setup")
	//	float SprungMass = 10;
	

	//components

	//Sprung Mass - Axle Component 
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* SprungAxleComponent = nullptr;

	//PhysConstraint -  base component (root) - springs axle
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* SpringConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* WheelComponent = nullptr;

	//PhysConstraint
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;


	// Sets default values for this actor's properties
	ASprungWheel();

private:
	//connect constraint to components at attachement
	void SetComponents();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
