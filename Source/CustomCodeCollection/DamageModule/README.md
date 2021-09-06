# Table Of Contents
- [Table Of Contents](#table-of-contents)
- [Inicial Setup](#inicial-setup)
- [Rundown and how to use The Weapons](#rundown-and-how-to-use-the-weapons)
	- [AProjectileBase](#aprojectilebase)
		- [Setupt](#setupt)
		- [Projectile options](#projectile-options)
	- [AWeaponBase](#aweaponbase)
	- [UWeaponHolderComponent](#uweaponholdercomponent)
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
4. Create a child class of UUserWidget named WBP_DamageNumbersWidget
5. Change the parent class to UDamageNumbersWidget
6. Copy the WBP_DamageNumbersWidget from this project:

# Rundown and how to use The Weapons
In this section we will show the damage module main features of this module and how to use them

## AProjectileBase

This is what the objects of the class AGunBase use to shoot and there exists two types of prjectiles:

1. **AHitScanProjectileBase:** this is a hitscan projectile meaning that the bulled has instantaneous travel speed, achieved through a line trace made by the AGunBase when spawning the projectile.
   
2. **ANonHitScanProjectileBase:** this is a non hit scan projectile meaning it has travel time, this is achieved through UE's UProjectileMovementComponent.

### Setupt

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
  
  ![ANonHitScanProjectileBase_Setup_2](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/ANonHitScanProjectileBase_Setup_2.png)

  - PBP == Projectile BluePrint
  - Set The Mesh:

	![ANonHitScanProjectileBase_Setup_3](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/ANonHitScanProjectileBase_Setup_3.png)

  - Set the atributes for the UProjectileMovementComponent:

	![ANonHitScanProjectileBase_Setup_4](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/ANonHitScanProjectileBase_Setup_4.png)

  - Set the atributes for the URotatingMovementComponent:

	![ANonHitScanProjectileBase_Setup_5](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/ANonHitScanProjectileBase_Setup_5.png)

  - Set the colision options:

	![ANonHitScanProjectileBase_Setup_6](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/ANonHitScanProjectileBase_Setup_6.png)

  - Finally Set the desired projectile options
  
### Projectile options
- These are options that are comun to both ANonHitScanProjectileBase and AHitScanProjectileBase
- AProjectileBase options:
  	
	![Projectile_options_1]()

	- **Can Explode:** if true the projectile will explode when it hits
	- **Explosion Delay:** the delay after the projectile actor registers a hit event to explode on seconds
	- **Explosion Radious:** the radious of the explosion
- Hit Particles options:
  
	![Projectile_options_2]()

  - this is the particles that will appear when the projectile hits a surface
- Explosion Particles options:
  
	![Projectile_options_3]()

  - this is the particles that will appear when the projectile explodes

- Hit Damage Component options:
  
	![Projectile_options_4]()

  - this is the Damage info that will be used when the projectile hits a ADamageableCharacter
  - **Damage Numbers Widget Class:** the class of the DamageNumbers that will be spawned in the damage instance, if left empty no floating damage numbers will be spawned
  - **Damage:** the base damage
  - **Damage Type:** to be implemented by the end user, this is the status effect of the damage instance and are intended to be handled (its effects on the damaged actor) in the UHealthComponent
  - **Crit Chance:** the chance of criting, it allows for percentages hover 1, if this is the case it can red crit like in warframe, and the out damge of a crit is equal to the crit damage to the power of the crit lvl times the damage
  - **Crit Damage:** the multiplier that will be applied to the damage when it crits
  - **Options under the charge tab:** this is how the corresponding stat varies acording to the charge percentage, for example in the "Damage Charge Variation" if the charge percentage is 0.5 then the damage will be 0.5*Damage. This is only used in charge weapons, any other weapon the charge percentage is 1 by default

- Explosion Damage Component options:
  
	![Projectile_options_5]()

  - this is the Damage info that will be used when the projectile explodes near a ADamageableCharacter
  - Has the same attributes as the Hit Damage Component

## AWeaponBase

This is the basic class of the weapons, this has the following child classes:

1. **AGunBase:** the base of all weapons that spawn projectiles
   1. **ASemiAutoGunBase:** semi auto fire
   2. **AFullyAutoGunBase:** full auto fire
   3. **AChargeGunBase:** charge fire
   4. **ABurstGunBase:** burst fire
2. **AMeleeBase:** to be implementaded
3. **AWeaponAgregateBase:** a agregate of several AWeaponBase each with its own id, used for weapons with alternate fire modes
   1. **AFireModeToggleAgregateBase:** same as AWeaponAgregateBase but when you use the alternate fire it will scroll through the diferent AWeaponBase


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

# Tips
