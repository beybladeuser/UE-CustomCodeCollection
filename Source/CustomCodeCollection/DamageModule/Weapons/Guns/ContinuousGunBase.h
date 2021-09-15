// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunBase.h"
#include "ContinuousGunBase.generated.h"

class AContinuousProjectileBase;

/**
 * 
 */
UCLASS()
class CUSTOMCODECOLLECTION_API AContinuousGunBase : public AGunBase
{
	GENERATED_BODY()

protected:
	AContinuousProjectileBase* HandledProjectile = nullptr;

	//X == firing time; Y == fire rate percentage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireOptions")
	FRuntimeFloatCurve SpoolUpCurve;

	FKeyHandle SpoolUpCurveDefaultHandle1;
	FKeyHandle SpoolUpCurveDefaultHandle2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireOptions")
	float SpoolResetTime = 0.f;
	FTimerHandle SpoolResetHandle;


	bool bIsFiring = false;
	//Handle Responsible for the looping that notifies a new damage tick to the bullet
	FTimerHandle AutoFireHandle;
	float ElapsedTime = 0.f;

	bool WaitingForReloadEnd = false;

	virtual float GeFireRate() override;

	void HandleContinuousFire();

	void ResetElapsedTime();

	void StartSpoolReset();

	void SpawnContinuousProjectile();

public:
	AContinuousGunBase();

	virtual void Tick(float DeltaTime) override;

	virtual void StartUsingWeapon() override;
	virtual void StopUsingWeapon() override;

	virtual void Reload() override;
};
