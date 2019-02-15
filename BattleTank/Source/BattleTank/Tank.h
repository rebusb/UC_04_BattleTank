// RebusStudios 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Delegate.h"

#include "Tank.generated.h"


//Declare delegate type
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	//Called by Engine when actor damage is delt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	//Used in blueprint to display health
	UFUNCTION(BlueprintPure, Category = "Damage")
		const float GetHealthPercent();

	//Broadcast (to controllers) when health is gone
	FTankDelegate OnDeath;

protected:
	void BeginPlay() override;

private:
	// Sets default values for this pawn's properties
	ATank();

	// track damage via health countdown
	int32 CurrentHealth;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		int32 InitialHealth = 20;

};
