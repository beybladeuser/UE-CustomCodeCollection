// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAgregateBase.h"
#include "../../Components/SceneComponents/ChildWeaponBaseComponent.h"
#include "../WeaponBase.h"

// Sets default values
AWeaponAgregateBase::AWeaponAgregateBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AWeaponAgregateBase::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UChildWeaponBaseComponent*> ChildWeapons = GetAllWeaponsChildren();

	for (UChildWeaponBaseComponent* ChildWeapon : ChildWeapons)
	{
		AWeaponBase* ContainedWeapon = ChildWeapon->GetChild<AWeaponBase>();

		if (ContainedWeapon)
		{
			ContainedWeapon->SetAmmoComponentInstance(AmmoComponent);
		}
	}
}

TArray<UChildWeaponBaseComponent*> AWeaponAgregateBase::GetAllWeaponsChildren_Implementation()
{
	TArray<UChildWeaponBaseComponent*> ChildWeapons;
	GetComponents(ChildWeapons, true);
	return ChildWeapons;
}

AWeaponBase* AWeaponAgregateBase::GetWeaponByID(int32 ID)
{
	UChildActorComponent* TempResult = nullptr;
	TArray<UChildWeaponBaseComponent*> ChildWeapons = GetAllWeaponsChildren();
	
	if (ChildWeapons.Num() <= ID)
	{
		UE_LOG(LogTemp, Warning, TEXT("ID %i is invalid for AWeaponAgregateBase Actor %s"), ID, *GetName());
		return nullptr;
	}
	if (ChildWeapons[ID])
	{
		return ChildWeapons[ID]->GetChild<AWeaponBase>();
	}
	return nullptr;
}

void AWeaponAgregateBase::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);

	TArray<UChildWeaponBaseComponent*> ChildWeapons;
	GetComponents(ChildWeapons, true);

	for (UChildWeaponBaseComponent* ChildWeapon : ChildWeapons)
	{
		AWeaponBase* ContainedWeapon = ChildWeapon->GetChild<AWeaponBase>();

		if (ContainedWeapon)
		{
			ContainedWeapon->SetOwner(NewOwner);
		}
	}
}

void AWeaponAgregateBase::SetActorHiddenInGame(bool bNewHidden)
{
	Super::SetActorHiddenInGame(bNewHidden);

	TArray<UChildWeaponBaseComponent*> ChildWeapons = GetAllWeaponsChildren();

	for (UChildWeaponBaseComponent* ChildWeapon : ChildWeapons)
	{
		AWeaponBase* ContainedWeapon = ChildWeapon->GetChild<AWeaponBase>();

		if (ContainedWeapon)
		{
			ContainedWeapon->SetActorHiddenInGame(bNewHidden);
		}
	}
}

void AWeaponAgregateBase::StartUsingWeapon()
{
	Super::StartUsingWeapon();

	bHasRecomputedAmmoInstance = true;
	StartUsingChildWeapon(0);
	bHasRecomputedAmmoInstance = false;
}

void AWeaponAgregateBase::StopUsingWeapon()
{
	Super::StopUsingWeapon();

	bHasRecomputedAmmoInstance = true;
	StopUsingChildWeapon(0);
	bHasRecomputedAmmoInstance = false;
}

void AWeaponAgregateBase::StartUsingChildWeapon(int32 FireModeID)
{
	if (!bAllowConcurentFiring)
	{
		for (int32 i = 0; i < GetAllWeaponsChildren().Num(); i++)
		{
			StopUsingChildWeapon(i);
		}
	}
	AWeaponBase* Weapon = GetWeaponByID(FireModeID);
	if (Weapon)
	{
		if (!bHasRecomputedAmmoInstance)
		{
			RefreshAmmoComponentInstance();
		}
		Weapon->SetAmmoComponentInstance(AmmoComponent);
		Weapon->StartUsingWeapon();
	}
}

void AWeaponAgregateBase::StopUsingChildWeapon(int32 FireModeID)
{
	AWeaponBase* Weapon = GetWeaponByID(FireModeID);
	if (Weapon)
	{
		if (!bHasRecomputedAmmoInstance)
		{
			RefreshAmmoComponentInstance();
		}
		Weapon->SetAmmoComponentInstance(AmmoComponent);
		Weapon->StopUsingWeapon();
	}
}

// Called every frame
void AWeaponAgregateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

