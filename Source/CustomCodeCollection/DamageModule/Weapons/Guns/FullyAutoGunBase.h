// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunBase.h"
#include "Curves/CurveFloat.h"
#include "FullyAutoGunBase.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMCODECOLLECTION_API AFullyAutoGunBase : public AGunBase
{
	GENERATED_BODY()
	
protected:
	//X == firing time; Y == fire rate percentage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireOptions")
	FRuntimeFloatCurve SpoolUpCurve;
	
	FKeyHandle SpoolUpCurveDefaultHandle1;
	FKeyHandle SpoolUpCurveDefaultHandle2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireOptions")
	float SpoolResetTime = 0.f;
	FTimerHandle SpoolResetHandle;


	bool bIsFiring = false;
	FTimerHandle AutoFireHandle;
	float ElapsedTime = 0.f;

	virtual float GeFireRate() override;

	void HandleAutoFire();

	void ResetElapsedTime();

	void StartSpoolReset();

public:
	AFullyAutoGunBase();

	virtual void Tick(float DeltaTime) override;

	virtual void StartUsingWeapon() override;
	virtual void StopUsingWeapon() override;

	virtual void Reload() override;
};
