# Table Of Contents
- [Table Of Contents](#table-of-contents)
- [Inicial Setup](#inicial-setup)
- [Rundown and how to use The Weapons](#rundown-and-how-to-use-the-weapons)
	- [AProjectileBase](#aprojectilebase)
	- [UWeaponHolderComponent](#uweaponholdercomponent)
	- [AWeaponBase](#aweaponbase)
	- [AWeaponAgregateBase](#aweaponagregatebase)
- [Tips](#tips)

# Inicial Setup
To use this in your project you only need to:
1. Slap this entire folder in your project source
2. Change the api macro to your project name, for example:
```c++
   // Fill out your copyright notice in the Description page of Project Settings.

	#pragma once

	#include "CoreMinimal.h"
	#include "BaseClasses/WorldPositionedWidgetBase.h"
	#include "../../Components/ActorComponents/DamageComponent.h"
	#include "DamageNumbersWidget.generated.h"

	/**
	 * 
	 */
	UCLASS()
	class CUSTOMCODECOLLECTION_API UDamageNumbersWidget : public UWorldPositionedWidgetBase
	{
		GENERATED_BODY()

	public:
		UFUNCTION(BlueprintImplementableEvent)
		void SetDamageNumber(FDamageCompute Damage);
	};
```
```c++
   // Fill out your copyright notice in the Description page of Project Settings.

	#pragma once

	#include "CoreMinimal.h"
	#include "BaseClasses/WorldPositionedWidgetBase.h"
	#include "../../Components/ActorComponents/DamageComponent.h"
	#include "DamageNumbersWidget.generated.h"

	/**
	 * 
	 */
	UCLASS()
	class NEWPROJECTNAME_API UDamageNumbersWidget : public UWorldPositionedWidgetBase
	{
		GENERATED_BODY()

	public:
		UFUNCTION(BlueprintImplementableEvent)
		void SetDamageNumber(FDamageCompute Damage);
	};
```

**DONT FORGET TO USE THE FIND AND REPLACE TOOL TO CHANGE ALL CUSTOMCODECOLLECTION_API INTO THE DESIRED PROJECT NAME ALL AT ONCE**

3. Add the Niagara and UMG Modules to the .Build.cs like so:

```c#
// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class CustomCodeCollection : ModuleRules
{
	public CustomCodeCollection(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Niagara", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
```
4. Export and import WBP_DamageNumbersWidget

# Rundown and how to use The Weapons
In this section we will show the damage module main features of this module and how to use them

## AProjectileBase

This is what the objects of the class AGunBase use to shoot and there exists two types of prjectiles:

1. **AHitScanProjectileBase:** this is a hitscan projectile meaning that the bulled has instantaneous travel speed, achieved through a line trace made by the AGunBase when spawning the projectile.
   
2. **ANonHitScanProjectileBase:** this is a non hit scan projectile meaning it has travel time, this is achieved through UE's UProjectileMovementComponent.

- **AHitScanProjectileBase Setup:**
  - First create a child blueprint of the AHitScanProjectileBase class:

  ![AHitScanProjectileBase_Setup_1](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/AHitScanProjectileBase_Setup_1.png)
  
  - Set is name acording to the recomended template: HSPBP_\<SomeName\>:
  
  ![AHitScanProjectileBase_Setup_2](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/AHitScanProjectileBase_Setup_2.png)
  
  - HSPBP == HitScan Projectile BluePrint
  - Finally Set the desired projectile options

- **ANonHitScanProjectileBase Setup:**
  - First create a child blueprint of the ANonHitScanProjectileBase class:
  
  ![ANonHitScanProjectileBase_Setup_1](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/ANonHitScanProjectileBase_Setup_1.png)

  - Set is name acording to the recomended template: PBP_\<SomeName\>:
  
  ![ANonHitScanProjectileBase_Setup_2]()

  - PBP == Projectile BluePrint
  - Set The Mesh
  - Set the atributes for the UProjectileMovementComponent
  - Set the atributes for the URotatingMovementComponent
  - Finally Set the desired projectile options

## UWeaponHolderComponent
- **Setup:**
  
  1. Add a UWeaponHolderComponent in the desired actor (doesnt have to be a ACharacter like in the example), for example:
  	```c++
	//==============================in .h========================
	UCLASS()
	class NEWPROJECTNAME_API ADemoChar : public ACharacter
	{
		GENERATED_BODY()
		//other code

	public;
		ADemoChar();

	protected:
		//other code

		//the WeaponHolder ref
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UWeaponHolderComponent* WeaponHolder;

		//more code
	};

	//===============in .cpp=====================
	ADemoChar::ADemoChar()
	{
		//other setup code

		//creates the component
		WeaponHolder = CreateDefaultSubobject<UWeaponHolderComponent>(TEXT("WeaponHolder"));
	}
	```
	
	or
	
	![UWeaponHolderComponent_Setup_1](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/UWeaponHolderComponent_Setup_1.png)
	
  1. Attach the UWeaponHolderComponent to the mesh and bone that will hold weapons like so:
	```c++
	//in the .cpp
	ADemoChar::ADemoChar()
	{
		//other setup code

		//creates the component
		WeaponHolder = CreateDefaultSubobject<UWeaponHolderComponent>(TEXT("WeaponHolder"));

		//attaches the weapon holder to the Character Mesh and the bone WeaponSocket
		WeaponHolder->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));
	}
	```
	or
	
	![UWeaponHolderComponent_Setup_2](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/UWeaponHolderComponent_Setup_2.png)
  3. 

## AWeaponBase
This is a simple weapon class that can only perform one action this is achieved by the use of the following functions:

```c++
public:
	UFUNCTION(BlueprintCallable)
	virtual void StartUsingWeapon();
	UFUNCTION(BlueprintCallable)
	virtual void StopUsingWeapon();
```
These should be used when the player starts pressing the shoot input and stop pressing the input respectfully like so:
```c++
void ADog::ShootActiveWeapon()
{
	if (Weapons.Num() && bIsAiming)
	{
		Weapons[GetActiveWeaponIndex()]->StartUsingWeapon();
	}
}

void ADog::StopShootActiveWeapon()
{
	if (Weapons.Num() && bIsAiming)
	{
		Weapons[GetActiveWeaponIndex()]->StopUsingWeapon();
	}
}

void ADog::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &ADog::ShootActiveWeapon);
	InputComponent->BindAction("Shoot", EInputEvent::IE_Released, this, &ADog::StopShootActiveWeapon);
}
```

## AWeaponAgregateBase

# Tips
