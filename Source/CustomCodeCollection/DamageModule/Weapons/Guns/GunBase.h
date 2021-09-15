// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../WeaponBase.h"
#include "GunBase.generated.h"

class AProjectileBase;
class UArrowComponent;
class USoundBase;
class UNiagaraSystem;

//A Semi auto gun
UCLASS()
class CUSTOMCODECOLLECTION_API AGunBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* SpawnDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireOptions|FX")
	UNiagaraSystem* MuzzleFlashParticles = nullptr;
	UPROPERTY(EditAnywhere, Category = "FireOptions|FX")
	USoundBase* MuzzleSound = nullptr;

	FTimerHandle FireRateHandle;
	bool bCanFire = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireOptions", meta = (ClampMin = "0.01"))
	float FireRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireOptions|Aim Options")
	bool bUseProjectileSpawnPointRotation = false;
	//The max range that the aim will be corrected to hit the object that the user is looking at
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireOptions|Aim Options", meta = (ClampMin = "0", EditCondition = "!bUseProjectileSpawnPointRotation"))
	float MaxTraceRange = 20000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireOptions|Aim Options", meta = (ClampMin = "0", EditCondition = "!bUseProjectileSpawnPointRotation"))
	TEnumAsByte<ECollisionChannel> TraceChannel = ECollisionChannel::ECC_Visibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireOptions")
	TSubclassOf<AProjectileBase> ProjectileClass;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetCanFire(bool bNewVal);

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AProjectileBase* SpawnProjectile();

	virtual bool CanBeUsed() override;

	virtual float GeFireRate();

	virtual void NotifyChargePercentToProjectileDamageComps(AProjectileBase* ProjectileToNotify);

	void NotifyTraceToProjectile(AProjectileBase* Projectile, bool bWasTraceSuccessful, const FHitResult& Hit);
};
