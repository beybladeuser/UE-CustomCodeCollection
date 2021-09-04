// Fill out your copyright notice in the Description page of Project Settings.


#include "HitScanProjectileBase.h"

void AHitScanProjectileBase::NotifyTraceResult(bool bWasTraceSuccessful, const FHitResult& Hit)
{
	Super::NotifyTraceResult(bWasTraceSuccessful, Hit);

	if (bWasTraceSuccessful)
	{
		SetActorLocation(Hit.ImpactPoint);
		OnHit(nullptr, Hit.GetActor(), nullptr, FVector(), Hit);
	}
	else
	{
		DestroySelf();
	}
}