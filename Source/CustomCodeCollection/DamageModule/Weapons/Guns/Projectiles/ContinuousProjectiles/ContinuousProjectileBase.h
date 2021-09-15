// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectileBase.h"
#include "ContinuousProjectileBase.generated.h"

class UNiagaraComponent;

/**
 * 
 */
UCLASS()
class CUSTOMCODECOLLECTION_API AContinuousProjectileBase : public AProjectileBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UNiagaraComponent* ContinuousParticles;
	UPROPERTY(EditAnywhere, Category = "FX")
	USoundBase* ContinuousSound = nullptr;

	TArray<AActor*> DamagedActorOnPrevTick;

	virtual TArray<AActor*> GetActorsToDamage();

	virtual void DoDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;
public:
	AContinuousProjectileBase();

	void NotifyDamageTick();
	void StopContinuousFire();

	virtual void NotifyTraceResult(bool bWasTraceSuccessful, const FHitResult& Hit, const FVector& TraceStart, const FVector& TraceDirection, float TraceRange) override;
};
