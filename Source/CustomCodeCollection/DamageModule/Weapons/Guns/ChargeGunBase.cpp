// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargeGunBase.h"
#include "./Projectiles/ProjectileBase.h"

void AChargeGunBase::HandleAmmoComponent(float Charge)
{
	Super::HandleAmmoComponent(GetChargePercentage());
}

void AChargeGunBase::NotifyChargePercentToProjectileDamageComps(AProjectileBase* ProjectileToNotify)
{
	ProjectileToNotify->NotifyCharge(GetChargePercentage());
}

void AChargeGunBase::EndCharge(bool bIsPlayerInput)
{
	if (bIsPlayerInput)
	{
		bool bAllowedEarlyRelease = ChargeSettings.bCanEarlyRelease && GetWorldTimerManager().IsTimerActive(ChargeHandle);
		if (bAllowedEarlyRelease || bIsFullyChaged)
		{
			SpawnProjectile();
		}
		GetWorldTimerManager().ClearTimer(ChargeHandle);
		bIsFullyChaged = false;
	}
	else
	{
		bIsFullyChaged = true;
		bool bNonSpecifiedInstaRelease = ChargeSettings.FullChargeHoldTime == 0.f && ChargeSettings.bAutoReleaseAfterFullChargeHoldTimeOut;
		bool bCanAutoFire = ChargeSettings.bAutoReleaseAfterFullyCharge;
		bCanAutoFire = bCanAutoFire || bNonSpecifiedInstaRelease;
		if (bCanAutoFire)
		{
			SpawnProjectile();
			bIsFullyChaged = false;
		}
		else if (ChargeSettings.FullChargeHoldTime > 0.f)
		{
			GetWorldTimerManager().SetTimer(FullChargeHoldHandle, this, &AChargeGunBase::HandleFullChargeHoldTimeOut, ChargeSettings.FullChargeHoldTime);
		}

	}
}

void AChargeGunBase::HandleFullChargeHoldTimeOut()
{
	if (ChargeSettings.bAutoReleaseAfterFullChargeHoldTimeOut)
	{
		SpawnProjectile();
	}
	bIsFullyChaged = false;
	GetWorldTimerManager().ClearTimer(ChargeHandle);
	GetWorldTimerManager().ClearTimer(FullChargeHoldHandle);
}

AChargeGunBase::AChargeGunBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ChargeCurve.EditorCurveData.AddKey(0.f, 0.f, true, ChargeCurveDefaultHandle1);
	ChargeCurve.EditorCurveData.AddKey(1.f, 1.f, true, ChargeCurveDefaultHandle2);
}

void AChargeGunBase::StartUsingWeapon()
{
	float ChargeTime = ChargeCurve.EditorCurveData.GetLastKey().Time;
	FTimerDelegate ChargeDelegate = FTimerDelegate::CreateUObject(this, &AChargeGunBase::EndCharge, false);
	GetWorldTimerManager().SetTimer(ChargeHandle, ChargeDelegate, ChargeTime, false);
}

void AChargeGunBase::StopUsingWeapon()
{
	EndCharge(true);
}

void AChargeGunBase::Reload()
{
	bIsFullyChaged = false;
	GetWorldTimerManager().ClearTimer(ChargeHandle);
	GetWorldTimerManager().ClearTimer(FullChargeHoldHandle);
}

float AChargeGunBase::GetChargePercentage()
{
	if (bIsFullyChaged)
	{
		return ChargeCurve.EditorCurveData.GetLastKey().Value;
	}
	return ChargeCurve.EditorCurveData.Eval(GetWorldTimerManager().GetTimerElapsed(ChargeHandle));
}

void AChargeGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, .2f, FColor::Red,
		FString::Printf(TEXT("Charge Percentage is equal to: %f"), GetChargePercentage()));
}