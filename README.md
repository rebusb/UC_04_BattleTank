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
### Blueprint Spawnable Component

Creating Actor components that are available in Blueprint Editor. 
- Inherit from UActorComponent class
    Add new C++ class in UE, inherit from ActorComponent class (UActorComponent)
- declare as:  
    `UCLASS(ClassGroup=(SectionName), meta=(BlueprintSpawnableComponent)) ... `

notes: 
The SectionName is the heading the component will appear under in the "Add Component..." popup.
The comment above the class declaration will appear as tooltip in editor.



### Delegates
#### Implementing Dynamic Multicast Delegates

On Broadcast Class:
- create Delegate Subject Name Type with macro call above class declaration
  - `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSubjectNameType);`
- declare DelegateBroadcaster as NameType in class
  - `FSubjectNameType OnEvent;`
- broadcast event
  - `OnEvent.Broadcast();`

On Receiver Class:
- Declare Delegate method
  - `UFUNCTION() void OnEventDelegate();`
- Register Delegate method in source
  - `BroadcastClass->OnEvent.AddUniqueDynamic(this, &ReceiverClass::OnEventDelegate);`
  
There are a multitude of DECLARE_DELEGATE_{paramsType}(...) signatures to cover:
DELEGATEs, DYNAMIC_DELEGATEs, MULTICAST_DELEGATEs, DYNAMIC_MULTICLASS_DELEGATES with or without ReturnValues (RetVal) and between zero and 8 passed parameters.

###### ex. 
`<RetVal> Function(); ==> DECLARE_DELEGATE_RetVal(RetValType,DelegateName); `

`Function(<Param1>, Param2>); ==> DECLARE_DELEGATE(DelegateName,Param1Type,Param2Type);`