// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "../../../Components/ActorComponents/DamageComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HitDamageComponent = CreateDefaultSubobject<UDamageComponent>("HitDamageComponent");
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectileBase::DestroySelf()
{
	GetWorld()->DestroyActor(this);
}

void AProjectileBase::NotifyIgnoredActor(AActor* ActorToIgnore)
{

}

void AProjectileBase::NotifyTraceResult(bool bWasTraceSuccessful, const FHitResult& Hit, const FVector& TraceStart, const FVector& TraceDirection, float TraceRange)
{

}

void AProjectileBase::NotifyCharge(float Charge)
{
	ChargePercentage = Charge;
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

