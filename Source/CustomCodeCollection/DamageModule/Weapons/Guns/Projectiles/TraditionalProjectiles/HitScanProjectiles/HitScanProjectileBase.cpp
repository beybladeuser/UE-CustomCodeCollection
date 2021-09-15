// Fill out your copyright notice in the Description page of Project Settings.


#include "HitScanProjectileBase.h"

void AHitScanProjectileBase::NotifyTraceResult(bool bWasTraceSuccessful, const FHitResult& Hit, const FVector& TraceStart, const FVector& TraceDirection, float TraceRange)
{
	Super::NotifyTraceResult(bWasTraceSuccessful, Hit, TraceStart, TraceDirection, TraceRange);

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