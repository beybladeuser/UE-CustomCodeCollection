// Fill out your copyright notice in the Description page of Project Settings.


#include "NonChargeMeleeBase.h"
#include "../../Components/ActorComponents/DamageComponent.h"

void ANonChargeMeleeBase::StartUsingWeapon()
{
	Super::StartUsingWeapon();

	if (CanBeUsed())
	{
		HandleNormalCombos();
		HandleAmmoComponent();
	}
}