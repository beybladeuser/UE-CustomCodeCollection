// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunBase.h"
#include "ChargeGunBase.generated.h"

USTRUCT(BlueprintType)
struct FChargeSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge Settings")
	bool bCanEarlyRelease = true;
	//If true the weapon will atomatically shoot after reaching a full charge
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge Settings")
	bool bAutoReleaseAfterFullyCharge = false;
	//Defines the time that the player can hold a full charge (Set -1 to enable the player to infinitly hold a full charge)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge Settings", meta = (ClampMin = "-1", EditCondition = "!bAutoReleaseAfterFullyCharge"))
	float FullChargeHoldTime = -1.f;
	//If true the weapon will atomatically shoot after the time allowed to hold a full charge as ended, if false it simply loses charge
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge Settings", meta = (EditCondition = "!bAutoReleaseAfterFullyCharge"))
	bool bAutoReleaseAfterFullChargeHoldTimeOut = false;
};

/**
 * 
 */
UCLASS()
class CUSTOMCODECOLLECTION_API AChargeGunBase : public AGunBase
{
	GENERATED_BODY()
	
protected:
	//X == charge time; Y == Charge percentage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireOptions")
	FRuntimeFloatCurve ChargeCurve;
	
	FKeyHandle ChargeCurveDefaultHandle1;
	FKeyHandle ChargeCurveDefaultHandle2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireOptions")
	FChargeSettings ChargeSettings;

	FTimerHandle ChargeHandle;
	FTimerHandle FullChargeHoldHandle;
	bool bIsFullyChaged = false;


	virtual void HandleAmmoComponent(float Charge = 1.f) override;

	virtual void NotifyChargePercentToProjectileDamageComps(AProjectileBase* ProjectileToNotify) override;
	
	void EndCharge(bool bIsPlayerInput);

	void HandleFullChargeHoldTimeOut();

public:
	AChargeGunBase();

	virtual void StartUsingWeapon() override;
	virtual void StopUsingWeapon() override;

	virtual void Reload() override;
	
	float GetChargePercentage();

	virtual void Tick(float DeltaTime) override;
};
