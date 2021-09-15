// Fill out your copyright notice in the Description page of Project Settings.


#include "CapsuleProjectileBase.h"
#include "Components/CapsuleComponent.h"

TArray<AActor*> ACapsuleProjectileBase::GetActorsToDamage()
{
	TArray<AActor*> Result;
	Collision->GetOverlappingActors(Result);
	return Result;
}

ACapsuleProjectileBase::ACapsuleProjectileBase()
{
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));

	Collision->SetupAttachment(RootComponent);
	Collision->SetRelativeRotation(FVector(1.f, 0.f, 0.f).Rotation());

	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACapsuleProjectileBase::DoDamage);
}