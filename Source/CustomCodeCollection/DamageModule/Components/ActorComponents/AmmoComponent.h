// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AmmoComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CUSTOMCODECOLLECTION_API UAmmoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAmmoComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Options", meta = (ClampMin = "0"))
	int32 AmmoConsumedPerShot = 1;

	//If ReloadTime < 0 then this component will never end reloading, this is meant so that you are able to call EndReload() on a EndAnimation function in BP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Options", meta = (ClampMin = "-1"))
	float ReloadTime = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Options")
	bool bUseReloadableClip = true;
	//Current clip ammo and inicial clip ammo count
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Options", meta = (ClampMin = "0", EditCondition = "bUseReloadableClip"))
	int32 ClipAmmo = 31;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Options", meta = (ClampMin = "0", EditCondition = "bUseReloadableClip"))
	int32 MaxClipAmmo = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Options", meta = (ClampMin = "0", EditCondition = "bUseReloadableClip"))
	int32 MaxChamberAmmo = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Options", meta = (EditCondition = "!bUseReloadableClip"))
	bool bReloadAmmoReserveOverTime = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Options", meta = (EditCondition = "!bUseReloadableClip && bReloadAmmoReserveOverTime"))
	float StartOverTimeReloadDelay = 2.f;
	FTimerHandle OverTimeReloadTimerTimerHandle;

	//Current ammo reserve and inicial ammo reserve count
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Options", meta = (ClampMin = "0"))
	int32 AmmoReserve = 540;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Options", meta = (ClampMin = "0"))
	int32 MaxAmmoReserve = 540;

	//Defines the percentage of consumed ammo (in relation AmmoConsumedPerShot) depending on the charge levl
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Options")
	FRuntimeFloatCurve AmmoConsuptionByChargeCurve;

	FKeyHandle AmmoConsuptionByChargeCurveDefaultHandle1;
	FKeyHandle AmmoConsuptionByChargeCurveDefaultHandle2;

	FTimerHandle ReloadTimerHandle;

	// Called when the game starts
	virtual void BeginPlay() override;

	void StartOvertimeReload();

public:	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//ChargePercentage used for charge weapons that the amount of charge affects the ammo consumed
	void ConsumeAmmo(float ChargePercentage = 1.f);

	UFUNCTION(BlueprintCallable)
	void Reload();
	UFUNCTION(BlueprintCallable)
	void EndReload();

	bool IsReloading();
	bool NeedsToReload();
	bool IsReadyToFire();
};
