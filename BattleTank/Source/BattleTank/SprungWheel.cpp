// RebusStudios 2019

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	WheelComponent->AddForce(SprungAxleComponent->GetForwardVector()*ForceMagnitude);
}

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("SpringConstraint"));
	if (ensure(SpringConstraint))
	{
		SetRootComponent(SpringConstraint);
		//UE_LOG(LogTemp, Warning, TEXT("Created and rooted SpringCon"));

	}

	
	SprungAxleComponent = CreateDefaultSubobject<USphereComponent>(FName("SprungAxleComponent"));
	if (ensure(SprungAxleComponent))
	{
		SprungAxleComponent->SetupAttachment(RootComponent);
		
		
	}

	WheelComponent = CreateDefaultSubobject<USphereComponent>(FName("WheelComponent"));
	if (ensure(WheelComponent))
	{
		WheelComponent->SetupAttachment(SprungAxleComponent);
	}

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	if (ensure(AxleWheelConstraint))
	{
		AxleWheelConstraint->SetupAttachment(SprungAxleComponent);
		AxleWheelConstraint->SetConstrainedComponents(SprungAxleComponent, NAME_None, WheelComponent, NAME_None);
	}

	


	SpringConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0);
	SpringConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0);
	SpringConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0);
	SpringConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.0);
	SpringConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.0);
	SpringConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 0.0);
	SpringConstraint->SetLinearPositionDrive(false, false, true);
	SpringConstraint->SetLinearVelocityDrive(false, false, true);
	SpringConstraint->SetLinearPositionTarget(FVector::ZeroVector);
	SpringConstraint->SetLinearVelocityTarget(FVector::ZeroVector);
	SpringConstraint->SetLinearDriveParams(SpringStrength, SpringDamp, 0.0);



}

void ASprungWheel::SetComponents()
{


	if (auto ParentActor = GetAttachParentActor())
	{
		//UE_LOG(LogTemp, Warning, TEXT("SprungWheel Attached to %s"), *ParentActor->GetName());
		auto BaseComponent = Cast<UPrimitiveComponent>(ParentActor->GetRootComponent());
		if (ensure(BaseComponent))
		{
			SpringConstraint->SetConstrainedComponents(BaseComponent, NAME_None, SprungAxleComponent, NAME_None);
		}


	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SprungWheel Attached to NULL... Constrained Components not set"));
		return;
	}
	


}
// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	SetComponents();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

