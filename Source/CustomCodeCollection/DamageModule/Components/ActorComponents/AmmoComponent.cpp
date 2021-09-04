// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoComponent.h"

// Sets default values for this component's properties
UAmmoComponent::UAmmoComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	AmmoConsuptionByChargeCurve.EditorCurveData.AddKey(0.f, 0.f, true, AmmoConsuptionByChargeCurveDefaultHandle1);
	AmmoConsuptionByChargeCurve.EditorCurveData.AddKey(1.f, 1.f, true, AmmoConsuptionByChargeCurveDefaultHandle2);
}


// Called when the game starts
void UAmmoComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
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

bool UAmmoComponent::IsReloading()
{
	return GetOwner()->GetWorldTimerManager().IsTimerActive(ReloadTimerHandle);
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