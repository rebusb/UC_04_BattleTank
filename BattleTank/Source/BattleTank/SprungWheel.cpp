// RebusStudios 2019

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;


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
			AxleWheelConstraint->SetConstrainedComponents(SprungAxleComponent, NAME_None, WheelComponent, NAME_None);

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
	
	WheelComponent->SetNotifyRigidBodyCollision(true);
	WheelComponent->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

	SetComponents();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		// reset applied force post physics
		TotalForceMagnitude = 0;
	}
}

void  ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//apply current force magnitude when in contact
	ApplyForce();
}


void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	TotalForceMagnitude += ForceMagnitude;
}

void ASprungWheel::ApplyForce()
{
	WheelComponent->AddForce(SprungAxleComponent->GetForwardVector()*TotalForceMagnitude);
}