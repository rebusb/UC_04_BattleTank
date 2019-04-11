// RebusStudios 2019

#include "WheelSpawnPoint.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UWheelSpawnPoint::UWheelSpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//UE_LOG(LogTemp, Warning, TEXT("init WheelSpawnPoint"));
	// ...
}


// Called when the game starts
void UWheelSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	// Spawn the attachment actor
	auto Attachment = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass,GetComponentTransform());
	//UE_LOG(LogTemp, Warning, TEXT("Spawned Attachment: %s"), *Attachment->GetName());

	if (!Attachment) return;
	Attachment->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	//UE_LOG(LogTemp, Warning, TEXT("Attached to spawnPoint"));
	UGameplayStatics::FinishSpawningActor(Attachment, GetComponentTransform());
}


// Called every frame
void UWheelSpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

