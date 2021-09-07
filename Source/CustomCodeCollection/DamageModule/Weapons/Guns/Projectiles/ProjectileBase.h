// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class USphereComponent;
class UNiagaraComponent;
class UDamageComponent;
class USoundBase;

UCLASS()
class CUSTOMCODECOLLECTION_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UNiagaraComponent* HitParticles;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UNiagaraComponent* ExplosionParticles;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDamageComponent* HitDamageComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDamageComponent* ExplosionDamageComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	USoundBase* HitSound = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Explosives")
	bool bCanExplode = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Explosives", meta = (EditCondition = "bCanExplode"))
	float ExplosionDelay = 0.f;
	FTimerHandle ExplosionDelayHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Explosives", meta = (EditCondition = "bCanExplode"))
	float ExplosionRadious = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Explosives", meta = (EditCondition = "bCanExplode"))
	USoundBase* ExplosionSound = nullptr;

	bool bCanBeDestroyed = false;
	float ChargePercentage = 1.f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void StartDetonation();
	virtual void Detonate();

	void DamageActor(UDamageComponent* DamageComponent, AActor* OtherActor, const FHitResult& Hit, bool IsExplosion);

	void PerpareToDestroy(bool bIsExplosion);
	void DestroySelf();
public:
	virtual void NotifyTraceResult(bool bWasTraceSuccessful, const FHitResult& Hit);

	void NotifyCharge(float Charge);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
