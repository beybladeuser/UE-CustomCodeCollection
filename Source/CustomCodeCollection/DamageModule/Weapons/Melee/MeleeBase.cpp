// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeBase.h"
#include "Components/CapsuleComponent.h"
#include "../../Components/ActorComponents/DamageComponent.h"

void AMeleeBase::BeginPlay()
{
	Super::BeginPlay();

	CollisionProfileWhenOn = Collision->GetCollisionProfileName();

	//Collision->IgnoreActorWhenMoving(GetOwner(), true);

	SetCollisionTurnedOff(true);
}

void AMeleeBase::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HandleOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AMeleeBase::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

AMeleeBase::AMeleeBase()
{
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	HitDamageComponent = CreateDefaultSubobject<UDamageComponent>(TEXT("HitDamageComponent"));

	Collision->SetupAttachment(RootComponent);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AMeleeBase::OnOverlap);
}

void AMeleeBase::SetCollisionTurnedOff(bool bTurnOffCollision)
{
	if (bTurnOffCollision)
	{
		Collision->SetCollisionProfileName(TEXT("NoCollision"));
	}
	else
	{
		Collision->SetCollisionProfileName(CollisionProfileWhenOn);
	}
}