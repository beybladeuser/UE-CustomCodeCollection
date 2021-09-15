// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponInfoWidgetBase.h"

void UWeaponInfoWidgetBase::InitWeapons_Implementation(int32 EquippedWeapon_, const TArray<AWeaponBase*>& Weapons_)
{
    Weapons = Weapons_;
    EquippedWeapon = EquippedWeapon_;
}

void UWeaponInfoWidgetBase::NotifyWeaponSwap_Implementation(int32 NewEquippedWeapon)
{
    EquippedWeapon = NewEquippedWeapon;
}

AWeaponBase* UWeaponInfoWidgetBase::GetEquipedWeapon()
{
    if (0 <= EquippedWeapon && EquippedWeapon < Weapons.Num())
    {
        return Weapons[EquippedWeapon];
    }
    return nullptr;
}

TArray<AWeaponBase*> UWeaponInfoWidgetBase::GetAllWeapons()
{
    return Weapons;
}
