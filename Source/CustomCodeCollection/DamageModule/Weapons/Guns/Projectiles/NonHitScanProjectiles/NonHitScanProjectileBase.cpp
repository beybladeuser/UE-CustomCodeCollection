// Fill out your copyright notice in the Description page of Project Settings.


#include "NonHitScanProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "NiagaraComponent.h"

void ANonHitScanProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	if (bCanExplode && bTurnOffCollisionBeforeExplosion)
	{
		Collision->SetCollisionProfileName(TEXT("NoCollision"));
	}
}

ANonHitScanProjectileBase::ANonHitScanProjectileBase()
{
	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovement");

	RootComponent = Collision;

	Mesh->SetupAttachment(Collision);

	//RotatingMovement->RotationRate = FRotator(0.0f, 360.0f, 0.f);
	RotatingMovement->RotationRate = FRotator(0.0f, 0.0f, 0.f);
	ProjectileMovement->InitialSpeed = 1000.f;

	Collision->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	//Collision->SetNotifyRigidBodyCollision(true);

	Collision->OnComponentHit.AddDynamic(this, &ANonHitScanProjectileBase::OnHit);
}

void ANonHitScanProjectileBase::NotifyIgnoredActor(AActor* ActorToIgnore)
{
	Collision->IgnoreActorWhenMoving(ActorToIgnore, true);
}