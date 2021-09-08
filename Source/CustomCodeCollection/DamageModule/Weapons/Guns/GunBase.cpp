// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"
#include "Projectiles/ProjectileBase.h"
#include "TimerManager.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"

// Sets default values
AGunBase::AGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("ProjectileSpawnPoint");
	SpawnDirection = CreateDefaultSubobject<UArrowComponent>("SpawnDirection");

	ProjectileSpawnPoint->SetupAttachment(Mesh);
	SpawnDirection->SetupAttachment(ProjectileSpawnPoint);
}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGunBase::SetCanFire(bool bNewVal)
{
	bCanFire = bNewVal;
}

bool AGunBase::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (!OwnerController) { return false; }

	FVector Start;
	FVector End;
	if (bUseProjectileSpawnPointRotation)
	{
		Start = ProjectileSpawnPoint->GetComponentLocation();
		End = Start + ProjectileSpawnPoint->GetComponentRotation().Vector() * MaxTraceRange;

		ShotDirection = -ProjectileSpawnPoint->GetComponentRotation().Vector();
	}
	else
	{
		FVector OwnerViewPointLocation;
		FRotator OwnerViewPointRotation;

		OwnerController->GetPlayerViewPoint(OUT OwnerViewPointLocation, OUT OwnerViewPointRotation);
		Start = OwnerViewPointLocation;
		End = OwnerViewPointLocation + OwnerViewPointRotation.Vector() * MaxTraceRange;

		ShotDirection = -OwnerViewPointRotation.Vector();
	}

	//DrawDebugCamera(GetWorld(), OwnerViewPointLocation, OwnerViewPointRotation, 90, 2, FColor::Red, true);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	TArray<AActor*> LiveProjectiles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProjectileBase::StaticClass(), LiveProjectiles);
	Params.AddIgnoredActors(LiveProjectiles);

	return GetWorld()->LineTraceSingleByChannel
	(
		OUT Hit,
		Start,
		End,
		TraceChannel,
		Params
	);
}

AProjectileBase* AGunBase::SpawnProjectile()
{
	if (!ProjectileClass) {
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,
			FString::Printf(TEXT("No ProjectileClass selected in %s"), *GetName()));
		return nullptr;
	}
	if (CanBeUsed())
	{
		
		FHitResult Hit;
		FVector ShotDirection;
		FTransform Transform;
		bool bWasTraceSuccessful = GunTrace(Hit, ShotDirection);
		if (bWasTraceSuccessful)
		{
			FVector Direction = Hit.ImpactPoint - ProjectileSpawnPoint->GetComponentLocation();
			Transform = FTransform(Direction.Rotation(), ProjectileSpawnPoint->GetComponentLocation(), FVector(1.f, 1.f, 1.f));
		}
		else
		{
			FRotator Rotation;

			AController* OwnerController = GetOwnerController();
			if (OwnerController && !bUseProjectileSpawnPointRotation)
			{
				FVector OwnerViewPointLocation;
				FRotator OwnerViewPointRotation;

				OwnerController->GetPlayerViewPoint(OUT OwnerViewPointLocation, OUT OwnerViewPointRotation);

				Rotation = OwnerViewPointRotation;
			}
			else
			{
				Rotation = ProjectileSpawnPoint->GetComponentRotation();
			}
			Transform = FTransform(Rotation, ProjectileSpawnPoint->GetComponentLocation(), FVector(1.f, 1.f, 1.f));
		}

		//Projectile Spawn
		AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, Transform);
		Projectile->SetOwner(GetOwner());
		Projectile->NotifyIgnoredActor(GetOwner());
		TArray<UPrimitiveComponent*> Collisions;
		GetOwner()->GetComponents(Collisions, true);
		for (UPrimitiveComponent* Collision : Collisions)
		{
			Collision->IgnoreActorWhenMoving(Projectile, true);
		}
		NotifyChargePercentToProjectileDamageComps(Projectile);
		Projectile->NotifyTraceResult(bWasTraceSuccessful, Hit);
		
		//Shot FX
		//SpawnSystemAttached(UNiagaraSystem * SystemTemplate, USceneComponent * AttachToComponent, FName AttachPointName, FVector Location, FRotator Rotation, EAttachLocation::Type LocationType, bool bAutoDestroy
		UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFlashParticles, ProjectileSpawnPoint, FName(), FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f), EAttachLocation::SnapToTarget, true);
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, ProjectileSpawnPoint);

		//Fire Rate Handling
		bCanFire = false;
		FTimerDelegate FireRateDelegate = FTimerDelegate::CreateUObject(this, &AGunBase::SetCanFire, true);
		GetWorldTimerManager().SetTimer(FireRateHandle, FireRateDelegate, 1.f / GeFireRate(), false);

		//Ammo Handling
		HandleAmmoComponent();

		return Projectile;
	}
	return nullptr;
}

bool AGunBase::CanBeUsed()
{

	return Super::CanBeUsed() && bCanFire;
}

float AGunBase::GeFireRate()
{
	if (FireRate <= 0.01f)
	{
		return 0.01;
	}
	return FireRate;
}

void AGunBase::NotifyChargePercentToProjectileDamageComps(AProjectileBase* ProjectileToNotify)
{

}