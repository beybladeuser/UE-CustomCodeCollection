// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");

	RootComponent = Mesh;

	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UAmmoComponent*> AmmoComponents;
	GetComponents(AmmoComponents, true);
	if (AmmoComponents.Num())
	{
		AmmoComponent = AmmoComponents[0];
	}
}

bool AWeaponBase::CanBeUsed()
{
	if (AmmoComponent)
	{
		return AmmoComponent->IsReadyToFire();
	}
	return true;
}

void AWeaponBase::HandleAmmoComponent(float Charge)
{
	if (AmmoComponent)
	{
		AmmoComponent->ConsumeAmmo(Charge);
		if (AmmoComponent->NeedsToReload())
		{
			AmmoComponent->Reload();
		}
	}
}

void AWeaponBase::RefreshAmmoComponentInstance()
{
	//updates the AmmoComponent, because when you modify the values of the AmmoComponent
	//in a instance the pointer can change making the prev pointer useless eventually
	//crashing the engine
	TArray<UAmmoComponent*> AmmoComponents;
	GetComponents(AmmoComponents, true);
	if (AmmoComponents.Num())
	{
		AmmoComponent = AmmoComponents[0];
	}
}

void AWeaponBase::StartUsingWeapon()
{
	RefreshAmmoComponentInstance();
	OnStartUsingWeapon();
}
void AWeaponBase::StopUsingWeapon()
{
	RefreshAmmoComponentInstance();
	OnStopUsingWeapon();
}

void AWeaponBase::Reload()
{
	if (AmmoComponent)
	{
		AmmoComponent->Reload();
		OnStartReload();
	}
}

AController* AWeaponBase::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) { return nullptr; }
	return OwnerPawn->GetController();
}

UAmmoComponent* AWeaponBase::GetAmmoComponent()
{
	return AmmoComponent;
}

void AWeaponBase::SetAmmoComponentInstance(UAmmoComponent* AmmoComponentInst)
{
	AmmoComponent = AmmoComponentInst;
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

