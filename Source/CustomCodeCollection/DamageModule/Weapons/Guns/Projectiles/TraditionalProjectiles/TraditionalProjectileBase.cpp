// Fill out your copyright notice in the Description page of Project Settings.


#include "TraditionalProjectileBase.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../../../../Components/ActorComponents/DamageComponent.h"

// Sets default values
ATraditionalProjectileBase::ATraditionalProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ExplosionDamageComponent = CreateDefaultSubobject<UDamageComponent>("ExplosionDamageComponent");
}

void ATraditionalProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//ignore more than 1 hit
	if (GetWorldTimerManager().IsTimerActive(ExplosionDelayHandle)) { return; }
	
	//FX
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitParticles, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

	//damage the actor
	HitDamageComponent->DamageActor(ChargePercentage, OtherActor, Hit, false);

	//setup the explosion
	if (bCanExplode)
	{
		if (ExplosionDelay)
		{
			StartDetonation();
		}
		else
		{
			Detonate();
		}
	}
	else
	{
		DestroySelf();
	}
}

void ATraditionalProjectileBase::StartDetonation()
{
	GetWorld()->GetTimerManager().SetTimer(ExplosionDelayHandle, this, &ATraditionalProjectileBase::Detonate, ExplosionDelay);
}

void ATraditionalProjectileBase::Detonate()
{
	//FX
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionParticles, GetActorLocation(), FRotator());
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, GetActorLocation(), FRotator());

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (GetDistanceTo(Actor) <= ExplosionRadious)
		{
			FHitResult Hit;
			ExplosionDamageComponent->DamageActor(ChargePercentage, Actor, Hit, true);
		}
		
	}

	DestroySelf();
}

