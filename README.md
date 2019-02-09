# UC_04_BattleTank
## Learning Unreal Engine through tanks and shooting and stuff
 Continuing the journey to the jade temple in the sky... 
 
## Useful links and other info
[markdown syntax](https://guides.github.com/features/mastering-markdown/)

## Syntax Guides
### Enums
```C++
UENUM()
enum class EThing : uint8
{
    Thing1,
    Thing2
}

// New property
UPROPERTY()
EThing MyProperty;
```
refer to enums using EThing as type, EThing::Thin1 as value
`EThing enumeratedValue = EThing::Thing2;`

### Blueprint Implementable Event

Will create a custom event available in Blueprints. Does not need definition in source code.

```C++
UFUNCTION(BlueprintImplementableEvent)
 TheFunction(AType VarToSend);
 
 TheFunction(VarToSend);

//from TankPlayerController.h
 	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);
		
//from TankPlayerController.cpp
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
 ```
