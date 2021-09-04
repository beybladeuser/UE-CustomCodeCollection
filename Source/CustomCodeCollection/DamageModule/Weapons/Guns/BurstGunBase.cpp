// Fill out your copyright notice in the Description page of Project Settings.


#include "BurstGunBase.h"

void ABurstGunBase::HandleBurst()
{
	if (CurrentBurstCount < ShotsPerBurst || bInfiniteBurst)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,
			FString::Printf(TEXT("Shots: %i"), CurrentBurstCount));
		GetWorldTimerManager().ClearTimer(FireRateHandle);
		SetCanFire(true);
		SpawnProjectile();
		CurrentBurstCount++;
		
		
		float DownTime = 1 / GeFireRate();
		if ((CurrentBurstCount < ShotsPerBurst || bInfiniteBurst) && FireRateOnBurst != 0.f)
		{
			DownTime = 1 / FireRateOnBurst;
		}
		GetWorldTimerManager().SetTimer(BurstHandle, this, &ABurstGunBase::HandleBurst, DownTime);
		
	}
	else
	{
		CurrentBurstCount = 0;
	}
}

void ABurstGunBase::StartUsingWeapon()
{
	Super::StartUsingWeapon();

	if (!GetWorldTimerManager().IsTimerActive(BurstHandle))
	{
		HandleBurst();
	}
}

void ABurstGunBase::Reload()
{
	Super::Reload();

	if (AmmoComponent && AmmoComponent->IsReloading())
	{
		GetWorldTimerManager().ClearTimer(BurstHandle);
	}
}