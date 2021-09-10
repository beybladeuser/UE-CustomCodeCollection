// Fill out your copyright notice in the Description page of Project Settings.


#include "NonChargeMeleeBase.h"
#include "../../Components/ActorComponents/DamageComponent.h"

void ANonChargeMeleeBase::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetOwner())
	{
		HitDamageComponent->DamageActor(1.f, OtherActor, SweepResult, false);
	}
}

void ANonChargeMeleeBase::StartUsingWeapon()
{
	Super::StartUsingWeapon();

	if (CanBeUsed())
	{
		HandleNormalCombos();
		HandleAmmoComponent();
	}
}