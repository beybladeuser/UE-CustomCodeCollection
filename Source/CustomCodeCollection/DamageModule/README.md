# Table Of Contents
- [Table Of Contents](#table-of-contents)
- [Inicial Setup](#inicial-setup)
- [Rundown and how to use The Weapons](#rundown-and-how-to-use-the-weapons)
	- [AProjectileBase](#aprojectilebase)
		- [Setupt](#setupt)
		- [Projectile options](#projectile-options)
	- [AWeaponBase](#aweaponbase)
		- [AGunBase](#agunbase)
		- [ASemiAutoGunBase](#asemiautogunbase)
		- [AFullyAutoGunBase](#afullyautogunbase)
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
  
  - Set is name acording to the recomended template: BPHSP_\<SomeName\>:
  
  ![AHitScanProjectileBase_Setup_2](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/AHitScanProjectileBase_Setup_2.png)
  
  - BPHSP == BluePrint HitScan Projectile
  - Finally Set the desired projectile options

- **ANonHitScanProjectileBase Setup:**
  - First create a child blueprint of the ANonHitScanProjectileBase class:
  
  ![ANonHitScanProjectileBase_Setup_1](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/ANonHitScanProjectileBase_Setup_1.png)

  - Set is name acording to the recomended template: BPP_\<SomeName\>:
  
  ![ANonHitScanProjectileBase_Setup_2](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/ANonHitScanProjectileBase_Setup_2.png)

  - BPP == BluePrint Projectile
  - Set The Mesh:

	![ANonHitScanProjectileBase_Setup_3](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/ANonHitScanProjectileBase_Setup_3.png)

  - Set the atributes for the UProjectileMovementComponent:

	![ANonHitScanProjectileBase_Setup_4](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/ANonHitScanProjectileBase_Setup_4.png)

  - Set the atributes for the URotatingMovementComponent:

	![ANonHitScanProjectileBase_Setup_5](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/ANonHitScanProjectileBase_Setup_5.png)

  - Set the colision options:

	![ANonHitScanProjectileBase_Setup_6](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/ANonHitScanProjectileBase_Setup_6.png)

  - Set the option **bTurnOffCollisionBeforeExplosion** this will turnoff the collision after the projectile hits, if true

	![ANonHitScanProjectileBase_Setup_7]()

  - Finally Set the desired projectile options
  
### Projectile options
- These are options that are comun to both ANonHitScanProjectileBase and AHitScanProjectileBase
- AProjectileBase options:
  	
	![Projectile_options_1](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/Projectile_options_1.png)

	- **Hit Sound:** the sound the projectile makes when it hits a surface
	- **Hit Particles:** this is the particles that will appear when the projectile hits a surface
	- **Can Explode:** if true the projectile will explode when it hits
	- **Explosion Delay:** the delay after the projectile actor registers a hit event to explode on seconds
	- **Explosion Radious:** the radious of the explosion
	- **Explosion Sound:** the sound the projectile makes when it explodes
	- **Explosion Particles:** this is the particles that will appear when the projectile explodes

- Hit Damage Component options:
  
	![Projectile_options_4](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/Projectile_options_4.png)

  - this is the Damage info that will be used when the projectile hits a ADamageableCharacter
  - **Damage Numbers Widget Class:** the class of the DamageNumbers that will be spawned in the damage instance, if left empty no floating damage numbers will be spawned
  - **Damage:** the base damage
  - **Damage Type:** to be implemented by the end user, this is the status effect of the damage instance and are intended to be handled (its effects on the damaged actor) in the UHealthComponent
  - **Crit Chance:** the chance of criting, it allows for percentages hover 1, if this is the case it can red crit like in warframe, and the out damge of a crit is equal to the crit damage to the power of the crit lvl times the damage
  - **Crit Damage:** the multiplier that will be applied to the damage when it crits
  - **Options under the charge tab:** this is how the corresponding stat varies acording to the charge percentage, for example in the "Damage Charge Variation" if the charge percentage is 0.5 then the damage will be 0.5*Damage. This is only used in charge weapons, any other weapon the charge percentage is 1 by default

- Explosion Damage Component options:
  
	![Projectile_options_5](https://github.com/beybladeuser/UE-CustomCodeCollection/blob/master/Source/CustomCodeCollection/DamageModule/README_IMGs/Projectile_options_5.png)

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
   
- **AWeaponBase Options**
	this options are common to all weapons
	
	![AWeaponBase_options_1]()

  - **Weapon Type:** an enum used for animations purposes, more specifically how to hold the weapon, you can add more in the WeaponBase.h file

- **AWeaponBase Overridable functions in BP:**
  - the following functions are designed to add animations/extra particles in blueprints, in c++ you would use StartUsingWeapon(), StopUsingWeapon() and Reload() directly. That Said here are the functions:
  - OnStartUsingWeapon()
  - StopUsingWeapon()
  - OnStartReload()

	```c++
	//in WeaponBase.cpp
	void AWeaponBase::StartUsingWeapon()
	{
		RefreshAmmoComponentInstance();
		OnStartUsingWeapon();
	}
	void AWeaponBase::StopUsingWeapon()
	{
		RefreshAmmoComponentInstance();
		OnStopUsingWeapon();
	}

	void AWeaponBase::Reload()
	{
		if (AmmoComponent)
		{
			AmmoComponent->Reload();
			OnStartReload();
		}
	}
	```
  
### AGunBase

This class isnt intended to create blueprint child classes so the following setup section will be for all AGunBase c++ child classes, because this setup is equal to all of them

- **Setup:**
  - First you create a child class of one of the AGunBase c++ child classes
  - Define the Mesh
  - Place the USceneComponent called Projectile Spawn Point at the end of the barrel of the gun (the arrow indicates the direction that the spawn point is facing)
  - Finally define the AGunBase Options
  
- **AGunBase Options**
  
  ![AGunBase_options_1]()

  - **Fire Rate:** the amount of projectiles the gun can shoot per second (the gun down time is 1 / Fire Rate)
  - **Projectile Class:** the AProjectileBase class that will be spawn wen the gun shoots
  - **Muzzle Flash Particles:** the particles that spawn when the gun shoots (they spawn at the Projectile Spawn Point USceneComponent location)
  - **Muzzle Sound:** the sound that the gun does when firing
  - **Use Projectile Spawn Point Rotation:** if this option is false the gun will make a trace to check where the player is facing (i.e. the camera, works with AI to though) and spawn the projectile in the direction of where the camera is facing, if true the projectile will spawn in the direction the AGunBase is physically facing (usefull for vehicle weapons like tank turrets or plane machine guns)
  - **Max Trace Range:** The range of the previously mentioned gun trace, thats done when Use Projectile Spawn Point Rotation==false
  - **Trace Channel:** The channel of the trace

### ASemiAutoGunBase

	this does not have anything diferent from AGunBase, except this actually shoots

### AFullyAutoGunBase

- **Setup:**
  - First do the same setup specified in AGunBase
  - Then Define the AFullyAutoGunBase Options

- **AFullyAutoGunBase Options**

	![AFullyAutoGunBase_options_1]()

	- **Spool Up Curve:** Defines how the fire rate will progress depending on how long the weapon is being fired (the downtime between shots(SDT) is calculated like so SDT = 1 / (SUC(ST) * FR), where SUC = Spool Up Curve, ST = time that the trigger is being held down, FR = Fire rate), for example in the prev image when you start to shoot the SDT = 1 / (0.1 * 20) and after 6 seconds the SDT = 1 / (1 * 20). **Note:** that fancy curve is achieved by changing the interpolation mode, this is done by right clicking the keys(i.e the white dots) and setting to auto, then you have to change the tangents. **Note2:** By Default the weapon doesnt spool up, so if you dont want the spool just set it to default.
	- **Spool Reset Time:** the time it takes after releasing the trigger so that the ST(time that the trigger is being held down) is set to 0, this is makes it so that you can stop shooting for a small amount of time and start again without having to wait for the spool up, making it feel better to shoot

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
