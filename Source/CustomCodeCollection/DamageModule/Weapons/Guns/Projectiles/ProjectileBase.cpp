// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../../../Components/ActorComponents/DamageComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HitDamageComponent = CreateDefaultSubobject<UDamageComponent>("HitDamageComponent");
	ExplosionDamageComponent = CreateDefaultSubobject<UDamageComponent>("ExplosionDamageComponent");
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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

void AProjectileBase::StartDetonation()
{
	GetWorld()->GetTimerManager().SetTimer(ExplosionDelayHandle, this, &AProjectileBase::Detonate, ExplosionDelay);
}

void AProjectileBase::Detonate()
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

void AProjectileBase::DestroySelf()
{
	GetWorld()->DestroyActor(this);
}

void AProjectileBase::NotifyIgnoredActor(AActor* ActorToIgnore)
{

}

void AProjectileBase::NotifyTraceResult(bool bWasTraceSuccessful, const FHitResult& Hit)
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

