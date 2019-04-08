// RebusStudios 2019

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup components
	BaseMassComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("BaseMassComponent"));
	if (ensure(BaseMassComponent))
	{
		SetRootComponent(BaseMassComponent);

		//set mass???
		//set physics active???
	}
	
	SprungMassComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("SprungMassComponent"));
	if (ensure(SprungMassComponent))
	{
		SprungMassComponent->SetupAttachment(RootComponent);
		
		//set mass???
		//set physics active???
	}

	SpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("SpringConstraint"));
	if (ensure(SpringConstraint))
	{
		SpringConstraint->SetupAttachment(RootComponent);
		SpringConstraint->SetConstrainedComponents(BaseMassComponent, NAME_None, SprungMassComponent, NAME_None);
		SpringConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked,0.0);
		SpringConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked,0.0);
		SpringConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0);
		SpringConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked,0.0);
		SpringConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked,0.0);
		SpringConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Free,0.0);
		SpringConstraint->SetLinearPositionDrive(false, false, true);
		SpringConstraint->SetLinearVelocityDrive(false, false, true);
		SpringConstraint->SetLinearPositionTarget(FVector::ZeroVector);
		SpringConstraint->SetLinearVelocityTarget(FVector::ZeroVector);
		SpringConstraint->SetLinearDriveParams(SpringStrength, SpringDamp, 0.0);

	}



}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

