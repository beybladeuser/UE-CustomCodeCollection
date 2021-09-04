// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectileBase.h"
#include "HitScanProjectileBase.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMCODECOLLECTION_API AHitScanProjectileBase : public AProjectileBase
{
	GENERATED_BODY()
	
public:
	virtual void NotifyTraceResult(bool bWasTraceSuccessful, const FHitResult& Hit) override;
};
