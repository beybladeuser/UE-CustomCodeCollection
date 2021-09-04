// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunBase.h"
#include "BurstGunBase.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMCODECOLLECTION_API ABurstGunBase : public AGunBase
{
	GENERATED_BODY()
	
protected:
	//(Its recomended that you have a AmmoComponent to use this setting)If set to true this will fire until the ammo has run out
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireOptions")
	bool bInfiniteBurst = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireOptions", meta = (EditCondition = "!bInfiniteBurst"))
	int32 ShotsPerBurst = 3;
	//Fire rate on the burst if equal to 0 then it will use the normal fire rate(if not then the inverse of the normal fire rate will be the downtime between the last shot of the burst and the next burst)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireOptions", meta = (ClampMin = "0"))
	float FireRateOnBurst = 0.f;

	int32 CurrentBurstCount = 0;

	FTimerHandle BurstHandle;

	void HandleBurst();

public:
	virtual void StartUsingWeapon() override;

	virtual void Reload() override;
};
