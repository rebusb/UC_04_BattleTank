// RebusStudios 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Setup")
		float SpringStrength = 100;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float SpringDamp = 10;

	//UPROPERTY(EditAnywhere, Category = "Setup")
	//	float BaseMass = 10;

	//UPROPERTY(EditAnywhere, Category = "Setup")
	//	float SprungMass = 10;
	

	//components
//Base Mass - ? this is not actually an object in tank... 
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* BaseMassComponent = nullptr;
	//Sprung Mass - ? also not a visible mesh component, how is this going to integrate with tank?
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* SprungMassComponent = nullptr;
	//PhysConstraint
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* SpringConstraint = nullptr;

	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
