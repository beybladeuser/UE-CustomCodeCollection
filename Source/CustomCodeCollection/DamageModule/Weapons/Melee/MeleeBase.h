// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../WeaponBase.h"
#include "MeleeBase.generated.h"

class UCapsuleComponent;
class UDamageComponent;

/**
 * 
 */
UCLASS()
class CUSTOMCODECOLLECTION_API AMeleeBase : public AWeaponBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDamageComponent* HitDamageComponent;

	FName CollisionProfileWhenOn;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	AMeleeBase();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleNormalCombos();

	void SetCollisionTurnedOff(bool bTurnOffCollision);
};
