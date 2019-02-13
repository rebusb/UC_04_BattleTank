// RebusStudios 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Tank.generated.h"







UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	//Called by Engine when actor damage is delt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:



private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		int32 CurrentHealth = 50;

};
