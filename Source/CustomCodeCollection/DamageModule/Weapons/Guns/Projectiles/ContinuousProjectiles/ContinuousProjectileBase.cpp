// Fill out your copyright notice in the Description page of Project Settings.


#include "ContinuousProjectileBase.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../../../../Components/ActorComponents/DamageComponent.h"

TArray<AActor*> AContinuousProjectileBase::GetActorsToDamage()
{
	return TArray<AActor*>();
}

void AContinuousProjectileBase::DoDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!DamagedActorOnPrevTick.Contains(OtherActor))
	{
		DamagedActorOnPrevTick.Add(OtherActor);
		HitDamageComponent->DamageActor(ChargePercentage, OtherActor, SweepResult, false);
	}
}

void AContinuousProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::SpawnSoundAttached(ContinuousSound, ContinuousParticles);
}

AContinuousProjectileBase::AContinuousProjectileBase()
{
	ContinuousParticles = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ContinuousParticles"));

	RootComponent = ContinuousParticles;
}

void AContinuousProjectileBase::NotifyDamageTick()
{
	DamagedActorOnPrevTick.Empty();
	for (AActor* ActorToDamage : GetActorsToDamage())
	{
		FHitResult HitResult;
		HitResult.ImpactPoint = ActorToDamage->GetActorLocation();
		HitResult.ImpactNormal = -this->GetActorForwardVector();
		DoDamage(nullptr, ActorToDamage, nullptr, 0, true, HitResult);
	}
}

void AContinuousProjectileBase::StopContinuousFire()
{
	DestroySelf();
}

void AContinuousProjectileBase::NotifyTraceResult(bool bWasTraceSuccessful, const FHitResult& Hit, const FVector& TraceStart, const FVector& TraceDirection, float TraceRange)
{
	Super::NotifyTraceResult(bWasTraceSuccessful, Hit, TraceStart, TraceDirection, TraceRange);

	if (bWasTraceSuccessful)
	{
		FVector Direction = Hit.ImpactPoint - GetActorLocation();
		SetActorRotation(Direction.Rotation());
	}
	else
	{
		SetActorRotation(TraceDirection.Rotation());
	}
}
