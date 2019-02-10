//General notes
//and code snippets taken from active code


/*	UE_LOG(LogTemp, Warning, TEXT("%s aims at %s with launch vel %s"),
			*GetOwner()->GetName(),
			*HitLocation.ToString(),
			*AimDirection.ToString());
*/


	const FName Tag = TEXT("TraceTag"); //////   much nicer debug trace!!!
	GetWorld()->DebugDrawTraceTag = Tag; /////
	FCollisionQueryParams Params(Tag);//////



	/// to quit the game gracefully:
#include "Kismet/KismetSystemLibrary.h"

		UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit);

		//logging for filters
		auto TankName = GetName();
		UE_LOG(LogTemp, Warning, TEXT("KITTY: %s in constructor"), *TankName);