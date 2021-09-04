// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../../../Components/ActorComponents/DamageComponent.h"
#include "../../../Characters/DamageableCharacter.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitParticles = CreateDefaultSubobject<UNiagaraComponent>("HitParticles");
	ExplosionParticles = CreateDefaultSubobject<UNiagaraComponent>("ExplosionParticles");
	HitDamageComponent = CreateDefaultSubobject<UDamageComponent>("HitDamageComponent");
	ExplosionDamageComponent = CreateDefaultSubobject<UDamageComponent>("ExplosionDamageComponent");

	ExplosionParticles->SetupAttachment(HitParticles);

	RootComponent = HitParticles;

	HitParticles->SetAutoActivate(false);
	ExplosionParticles->SetAutoActivate(false);

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (GetWorldTimerManager().IsTimerActive(ExplosionDelayHandle)) { return; }
	HitParticles->SetWorldLocation(Hit.ImpactPoint);
	HitParticles->SetWorldRotation(Hit.ImpactNormal.Rotation());
	HitParticles->SetActive(true);
	DamageActor(HitDamageComponent, OtherActor, Hit, false);
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
		bCanBeDestroyed = true;
	}
}

void AProjectileBase::StartDetonation()
{
	GetWorld()->GetTimerManager().SetTimer(ExplosionDelayHandle, this, &AProjectileBase::Detonate, ExplosionDelay);
}

void AProjectileBase::Detonate()
{
	ExplosionParticles->SetActive(true);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADamageableCharacter::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (GetDistanceTo(Actor) <= ExplosionRadious)
		{
			FHitResult Hit;
			DamageActor(ExplosionDamageComponent, Actor, Hit, true);
		}
		
	}

	bCanBeDestroyed = true;
}

void AProjectileBase::DamageActor(UDamageComponent* DamageComponent, AActor* OtherActor, const FHitResult& Hit, bool IsExplosion)
{
	FDamageCompute Damage = DamageComponent->ComputeFlatDamage(ChargePercentage);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
		FString::Printf(TEXT("Damage: %f"), Damage.Damage));
	APawn* OwnerPawn = GetOwner<APawn>();
	if (OwnerPawn)
	{
		if (ADamageableCharacter* Enemy = Cast<ADamageableCharacter>(OtherActor))
		{
			Enemy->AddDamage(Damage, OwnerPawn->GetController(), OwnerPawn, Hit, IsExplosion);
		}
		else
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage.Damage, OwnerPawn->GetController(), OwnerPawn, Damage.DamageType);
		}
	}
}

void AProjectileBase::DestroySelf()
{
	GetWorld()->DestroyActor(this);
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

	if (bCanBeDestroyed && !HitParticles->IsActive() && !ExplosionParticles->IsActive())
	{
		DestroySelf();
	}
}

