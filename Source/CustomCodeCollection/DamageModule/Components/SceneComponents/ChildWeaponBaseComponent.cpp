// Fill out your copyright notice in the Description page of Project Settings.


#include "ChildWeaponBaseComponent.h"
#include "../../Weapons/WeaponBase.h"

void UChildWeaponBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!WeaponClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid WeaponClass in UChildWeaponBaseComponent of actor %s"), *GetOwner()->GetName());
	}
	else
	{
		Weapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);
		Weapon->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

void UChildWeaponBaseComponent::StartUsingChildWeapon()
{
	AWeaponBase* WeaponChild = GetChild<AWeaponBase>();
	if (WeaponChild)
	{
		WeaponChild->StartUsingWeapon();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No AWeaponBase associated to UChildWeaponBaseComponent of Actor %s"), *GetOwner()->GetName());
	}
}

void UChildWeaponBaseComponent::StopUsingChildWeapon()
{

	AWeaponBase* WeaponChild = GetChild<AWeaponBase>();
	if (WeaponChild)
	{
		WeaponChild->StopUsingWeapon();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No AWeaponBase associated to UChildWeaponBaseComponent of Actor %s"), *GetOwner()->GetName());
	}
}
