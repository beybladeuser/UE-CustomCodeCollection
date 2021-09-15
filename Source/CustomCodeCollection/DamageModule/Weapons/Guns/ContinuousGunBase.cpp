// Fill out your copyright notice in the Description page of Project Settings.


#include "ContinuousGunBase.h"
#include "./Projectiles/ContinuousProjectiles/ContinuousProjectileBase.h"

float AContinuousGunBase::GeFireRate()
{
	float Result = Super::GeFireRate() * SpoolUpCurve.EditorCurveData.Eval(ElapsedTime);
	if (Result <= 0.01)
	{
		return 0.01f;
	}
	return Result;

}

void AContinuousGunBase::HandleContinuousFire()
{
	if (bIsFiring)
	{
		GetWorldTimerManager().ClearTimer(FireRateHandle);
		bCanFire = true;
		if (HandledProjectile)
		{
			HandledProjectile->NotifyDamageTick();
		}
		GetWorldTimerManager().SetTimer(AutoFireHandle, this, &AContinuousGunBase::HandleContinuousFire, 1 / GeFireRate());
	}
}

void AContinuousGunBase::ResetElapsedTime()
{
	ElapsedTime = 0.f;
}

void AContinuousGunBase::StartSpoolReset()
{
	if (SpoolResetTime <= 0.f)
	{
		ResetElapsedTime();
	}
	else
	{
		GetWorldTimerManager().SetTimer(SpoolResetHandle, this, &AContinuousGunBase::ResetElapsedTime, SpoolResetTime);
	}
}

void AContinuousGunBase::SpawnContinuousProjectile()
{
	HandledProjectile = Cast<AContinuousProjectileBase>(SpawnProjectile());
	if (!HandledProjectile)
	{
		UE_LOG(LogTemp, Warning, TEXT("in AContinuousGunBase %s, expected ProjectileClass to be of class AContinuousProjectileBase"), *GetName());
	}
	else
	{
		FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);

		HandledProjectile->AttachToComponent(ProjectileSpawnPoint, Rules);
		//HandledProjectile->SetActorRelativeTransform(FTransform(FRotator(0.f, 0.f, 0.f), FVector(0.f, 0.f, 0.f)));
	}
}

AContinuousGunBase::AContinuousGunBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SpoolUpCurve.EditorCurveData.AddKey(0.f, 1.f, true, SpoolUpCurveDefaultHandle1);
	SpoolUpCurve.EditorCurveData.AddKey(1.f, 1.f, true, SpoolUpCurveDefaultHandle2);
}

void AContinuousGunBase::Tick(float DeltaTime)
{
	bool bIsReloading = AmmoComponent && AmmoComponent->IsReloading();
	if (bIsFiring && !bIsReloading)
	{
		ElapsedTime = FMath::Clamp(ElapsedTime + DeltaTime, 0.f, SpoolUpCurve.EditorCurveData.GetLastKey().Time);
		if (WaitingForReloadEnd)
		{
			WaitingForReloadEnd = false;
			SpawnContinuousProjectile();
		}
	}
	if (HandledProjectile && bIsFiring)
	{
		FHitResult Hit;
		FVector ShotDirection;
		bool bWasTraceSuccessful = GunTrace(Hit, ShotDirection);
		NotifyTraceToProjectile(HandledProjectile, bWasTraceSuccessful, Hit);
	}
	
}

void AContinuousGunBase::StartUsingWeapon()
{
	Super::StartUsingWeapon();

	bIsFiring = true;
	GetWorldTimerManager().ClearTimer(SpoolResetHandle);
	if (!GetWorldTimerManager().IsTimerActive(AutoFireHandle))
	{
		SpawnContinuousProjectile();
		HandleContinuousFire();
	}
}

void AContinuousGunBase::StopUsingWeapon()
{
	StartSpoolReset();
	bIsFiring = false;
	if (HandledProjectile)
	{
		HandledProjectile->StopContinuousFire();
	}
}

void AContinuousGunBase::Reload()
{
	Super::Reload();

	if (AmmoComponent && AmmoComponent->IsReloading())
	{
		StartSpoolReset();
		WaitingForReloadEnd = true;
		if (HandledProjectile)
		{
			HandledProjectile->StopContinuousFire();
		}
	}
}