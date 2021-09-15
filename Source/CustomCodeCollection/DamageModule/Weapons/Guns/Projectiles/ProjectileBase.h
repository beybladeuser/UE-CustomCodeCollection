// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class USphereComponent;
class UNiagaraComponent;
class UDamageComponent;
class USoundBase;
class UNiagaraSystem;

UCLASS()
class CUSTOMCODECOLLECTION_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDamageComponent* HitDamageComponent;

	float ChargePercentage = 1.f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DestroySelf();
public:
	virtual void NotifyIgnoredActor(AActor* ActorToIgnore);
	//const FVector& TraceStart, const FVector& TraceDirection, float TraceRange should only be considered if bWasTraceSuccessful == false
	virtual void NotifyTraceResult(bool bWasTraceSuccessful, const FHitResult& Hit, const FVector& TraceStart, const FVector& TraceDirection, float TraceRange);

	void NotifyCharge(float Charge);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
