// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoComponent.h"

// Sets default values for this component's properties
UAmmoComponent::UAmmoComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	AmmoConsuptionByChargeCurve.EditorCurveData.AddKey(0.f, 0.f, true, AmmoConsuptionByChargeCurveDefaultHandle1);
	AmmoConsuptionByChargeCurve.EditorCurveData.AddKey(1.f, 1.f, true, AmmoConsuptionByChargeCurveDefaultHandle2);
}


// Called when the game starts
void UAmmoComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UAmmoComponent::StartOvertimeReload()
{
	if (ReloadTime >= 0.f)
	{
		GetOwner()->GetWorldTimerManager().SetTimer(ReloadTimerHandle, ReloadTime, false);
	}
}

void UAmmoComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bReloadAmmoReserveOverTime && GetOwner()->GetWorldTimerManager().IsTimerActive(ReloadTimerHandle))
	{
		float _ReloadTime = ReloadTime == 0.f ? 0.001 : ReloadTime;
		float ReloadedAmmoPerSecond = MaxAmmoReserve / _ReloadTime;
		float ReloadedAmmo = ReloadedAmmoPerSecond * DeltaTime;

		AmmoReserve = FMath::Clamp(AmmoReserve + (int32)FMath::RoundFromZero(ReloadedAmmo), 0, MaxAmmoReserve);
	}
}

void UAmmoComponent::ConsumeAmmo(float ChargePercentage)
{
	int32 AmmoToConsume = FMath::TruncToInt(AmmoConsumedPerShot * AmmoConsuptionByChargeCurve.EditorCurveData.Eval(ChargePercentage));
	AmmoToConsume = FMath::Clamp(AmmoToConsume + 1, 1, AmmoConsumedPerShot);
	if (bUseReloadableClip)
	{
		ClipAmmo = FMath::Clamp(ClipAmmo - AmmoToConsume, 0, MaxClipAmmo);
	}
	else
	{
		AmmoReserve = FMath::Clamp(AmmoReserve - AmmoToConsume, 0, MaxAmmoReserve);
		if (bReloadAmmoReserveOverTime)
		{
			GetOwner()->GetWorldTimerManager().ClearTimer(ReloadTimerHandle);
			GetOwner()->GetWorldTimerManager().ClearTimer(OverTimeReloadTimerTimerHandle);
			if (StartOverTimeReloadDelay > 0)
			{
				GetOwner()->GetWorldTimerManager().SetTimer(OverTimeReloadTimerTimerHandle, this, &UAmmoComponent::StartOvertimeReload, StartOverTimeReloadDelay);
			}
			else
			{
				StartOvertimeReload();
			}
		}
	}
}

void UAmmoComponent::Reload()
{
	if (!bUseReloadableClip) { return; }

	if (ReloadTime == 0.f)
	{
		EndReload();
	}
	else if (ReloadTime > 0.f)
	{
		GetOwner()->GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &UAmmoComponent::EndReload, ReloadTime);
	}
	else
	{
		GetOwner()->GetWorldTimerManager().SetTimer(ReloadTimerHandle, 9999.f, true);
	}
}

void UAmmoComponent::EndReload()
{
	if (!bUseReloadableClip) { return; }

	int32 AmmoInChamber = MaxChamberAmmo;
	if (ClipAmmo < MaxChamberAmmo)
	{
		AmmoInChamber = ClipAmmo;
	}
	int32 AmmoInClip = ClipAmmo - AmmoInChamber;
	int32 AmmoToReload = MaxClipAmmo - AmmoInClip;

	int32 ReloadedAmmo = AmmoToReload;
	if (AmmoToReload >= AmmoReserve)
	{
		ReloadedAmmo = AmmoReserve;
	}

	ClipAmmo = AmmoInChamber + ReloadedAmmo + AmmoInClip;
	AmmoReserve -= ReloadedAmmo;

	GetOwner()->GetWorldTimerManager().ClearTimer(ReloadTimerHandle);
}

bool UAmmoComponent::IsReloading()
{
	return GetOwner()->GetWorldTimerManager().IsTimerActive(ReloadTimerHandle) && !bReloadAmmoReserveOverTime;
}

bool UAmmoComponent::NeedsToReload()
{
	return ClipAmmo < AmmoConsumedPerShot;
}

bool UAmmoComponent::IsReadyToFire()
{
	bool bIsntReloading = !IsReloading();
	bool bHasAmmo;
	if (bUseReloadableClip)
	{
		bHasAmmo = !NeedsToReload();
	}
	else
	{
		bHasAmmo = AmmoReserve >= AmmoConsumedPerShot;
	}
	return bIsntReloading && bHasAmmo;
}