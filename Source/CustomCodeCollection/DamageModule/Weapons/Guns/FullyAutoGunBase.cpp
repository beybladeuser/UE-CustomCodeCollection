// Fill out your copyright notice in the Description page of Project Settings.


#include "FullyAutoGunBase.h"

float AFullyAutoGunBase::GeFireRate()
{
	float Result = Super::GeFireRate() * SpoolUpCurve.EditorCurveData.Eval(ElapsedTime);
	if (Result <= 0.01)
	{
		return 0.01f;
	}
	return Result;
	
}

void AFullyAutoGunBase::HandleAutoFire()
{
	if (bIsFiring)
	{
		GetWorldTimerManager().ClearTimer(FireRateHandle);
		bCanFire = true;
		SpawnProjectile();
		GetWorldTimerManager().SetTimer(AutoFireHandle, this, &AFullyAutoGunBase::HandleAutoFire, 1 / GeFireRate());
	}
}

void AFullyAutoGunBase::ResetElapsedTime()
{
	ElapsedTime = 0.f;
}

void AFullyAutoGunBase::StartSpoolReset()
{
	if (SpoolResetTime <= 0.f)
	{
		ResetElapsedTime();
	}
	else
	{
		GetWorldTimerManager().SetTimer(SpoolResetHandle, this, &AFullyAutoGunBase::ResetElapsedTime, SpoolResetTime);
	}
}

AFullyAutoGunBase::AFullyAutoGunBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SpoolUpCurve.EditorCurveData.AddKey(0.f, 1.f, true, SpoolUpCurveDefaultHandle1);
	SpoolUpCurve.EditorCurveData.AddKey(1.f, 1.f, true, SpoolUpCurveDefaultHandle2);
}

void AFullyAutoGunBase::Tick(float DeltaTime)
{
	bool bIsReloading = AmmoComponent && AmmoComponent->IsReloading();
	if (bIsFiring && !bIsReloading)
	{
		ElapsedTime = FMath::Clamp(ElapsedTime + DeltaTime, 0.f, SpoolUpCurve.EditorCurveData.GetLastKey().Time);
	}
}

void AFullyAutoGunBase::StartUsingWeapon()
{
	Super::StartUsingWeapon();

	bIsFiring = true;
	GetWorldTimerManager().ClearTimer(SpoolResetHandle);
	if (!GetWorldTimerManager().IsTimerActive(AutoFireHandle))
	{
		HandleAutoFire();
	}
}

void AFullyAutoGunBase::StopUsingWeapon()
{
	StartSpoolReset();
	bIsFiring = false;
}

void AFullyAutoGunBase::Reload()
{
	Super::Reload();

	if (AmmoComponent && AmmoComponent->IsReloading())
	{
		StartSpoolReset();
	}
}