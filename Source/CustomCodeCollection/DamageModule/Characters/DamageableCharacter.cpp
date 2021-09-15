// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageableCharacter.h"
#include "../Components/ActorComponents/HealthComponent.h"
#include "../Components/ActorComponents/DamageComponent.h"

// Sets default values
ADamageableCharacter::ADamageableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = CreateDefaultSubobject<UHealthComponent>("Health");
}

// Called when the game starts or when spawned
void ADamageableCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADamageableCharacter::AddDamage_Implementation(FDamageCompute Damage, AController* EventInstigator, AActor* DamageCauser, const FHitResult& Hit, bool bIsExplosion)
{
	Health->AddDamage(Damage, EventInstigator, DamageCauser, Hit, bIsExplosion);
}

void ADamageableCharacter::NotifyDeath_Implementation()
{
	K2_DestroyActor();
}

// Called every frame
void ADamageableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADamageableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

