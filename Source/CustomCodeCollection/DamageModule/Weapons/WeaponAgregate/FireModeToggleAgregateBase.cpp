// Fill out your copyright notice in the Description page of Project Settings.


#include "FireModeToggleAgregateBase.h"

void AFireModeToggleAgregateBase::ScrollFireMode(bool bScrollForward)
{
	int32 Sign = -1;
	if (bScrollForward)
	{
		Sign = 1;
	}
	ActiveFireMode += Sign;
	if (ActiveFireMode >= GetAllWeaponsChildren().Num())
	{
		ActiveFireMode = 0;
	}
	else if (ActiveFireMode < 0)
	{
		ActiveFireMode = GetAllWeaponsChildren().Num() - 1;
	}
}

void AFireModeToggleAgregateBase::StartUsingChildWeapon(int32 FireModeID)
{
	FireModeID = FMath::Clamp(FireModeID, 0, GetAllWeaponsChildren().Num());
	if (FireModeID != 0)
	{
		ScrollFireMode(true);
		return;
	}

	Super::StartUsingChildWeapon(ActiveFireMode);
}

void AFireModeToggleAgregateBase::StopUsingChildWeapon(int32 FireModeID)
{
	FireModeID = FMath::Clamp(FireModeID, 0, GetAllWeaponsChildren().Num());
	if (FireModeID != 0)
	{
		return;
	}
	Super::StopUsingChildWeapon(ActiveFireMode);
}