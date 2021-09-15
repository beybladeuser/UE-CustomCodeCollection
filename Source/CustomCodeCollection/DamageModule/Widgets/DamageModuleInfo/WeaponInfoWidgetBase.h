// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Weapons/WeaponBase.h"
#include "WeaponInfoWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMCODECOLLECTION_API UWeaponInfoWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	TArray<AWeaponBase*> Weapons;
	int32 EquippedWeapon;

public:
	UFUNCTION(BlueprintNativeEvent)
	void InitWeapons(int32 EquippedWeapon_, const TArray<AWeaponBase*>& Weapons_);

	UFUNCTION(BlueprintNativeEvent)
	void NotifyWeaponSwap(int32 NewEquippedWeapon);

	UFUNCTION(BlueprintPure)
	AWeaponBase* GetEquipedWeapon();

	UFUNCTION(BlueprintPure)
	TArray<AWeaponBase*> GetAllWeapons();
};
