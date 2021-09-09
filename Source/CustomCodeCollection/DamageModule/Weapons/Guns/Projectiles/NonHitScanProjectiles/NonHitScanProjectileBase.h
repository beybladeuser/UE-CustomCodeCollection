// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectileBase.h"
#include "NonHitScanProjectileBase.generated.h"

class UProjectileMovementComponent;
class URotatingMovementComponent;

/**
 * 
 */
UCLASS()
class CUSTOMCODECOLLECTION_API ANonHitScanProjectileBase : public AProjectileBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	URotatingMovementComponent* RotatingMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Explosives", meta = (EditCondition = "bCanExplode"))
	bool bTurnOffCollisionBeforeExplosion = true;

	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

public:
	ANonHitScanProjectileBase();

	virtual void NotifyIgnoredActor(AActor* ActorToIgnore) override;

};
