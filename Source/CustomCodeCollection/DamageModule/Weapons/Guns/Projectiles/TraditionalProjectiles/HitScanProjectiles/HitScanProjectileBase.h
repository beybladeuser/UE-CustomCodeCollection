// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../TraditionalProjectileBase.h"
#include "HitScanProjectileBase.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMCODECOLLECTION_API AHitScanProjectileBase : public ATraditionalProjectileBase
{
	GENERATED_BODY()
	
public:
	virtual void NotifyTraceResult(bool bWasTraceSuccessful, const FHitResult& Hit, const FVector& TraceStart, const FVector& TraceDirection, float TraceRange) override;
};
