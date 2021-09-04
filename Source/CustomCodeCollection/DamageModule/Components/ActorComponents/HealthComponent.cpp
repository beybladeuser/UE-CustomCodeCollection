// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "DamageComponent.h"
#include "GameFramework/DamageType.h"
#include "../../Widgets/WorldPositionedWidget/DamageNumbersWidget.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

float UHealthComponent::GetResistance(TSubclassOf<UDamageType> DamageType)
{
	if (float* Result = Resistences.Find(DamageType))
	{
		return *Result;
	}
	return 0.0f;
}

void UHealthComponent::ComputeDamageAfterDefence(FDamageCompute& Damage)
{
}

void UHealthComponent::ComputeDamageAfterResistance(FDamageCompute& Damage)
{
	float DamageRes = GetResistance(Damage.DamageType);
	Damage.Resistance = DamageRes;
	Damage.Damage *= 1 - DamageRes;
}

void UHealthComponent::ComputeDamageAfterStatus(FDamageCompute& Damage)
{

}

void UHealthComponent::HandleStatus()
{
}

void UHealthComponent::KillOwner()
{
	GetOwner()->K2_DestroyActor();
}

void UHealthComponent::AddDamage(FDamageCompute Damage, AController* EventInstigator, AActor* DamageCauser, const FHitResult& Hit, bool bIsExplosion)
{
	ComputeDamageAfterDefence(Damage);
	ComputeDamageAfterResistance(Damage);
	ComputeDamageAfterStatus(Damage);

	FVector Location;
	APawn* OwnerPawn = GetOwner<APawn>();
	if (!bIsExplosion)
	{
		Location = Hit.ImpactPoint;
	}
	else
	{
		Location = OwnerPawn->GetActorLocation();
	}

	UDamageNumbersWidget* DamageNumbers = nullptr;
	if (Damage.DamageNumbersWidgetClass)
	{
		DamageNumbers = Cast<UDamageNumbersWidget>(CreateWidget(GetWorld(), Damage.DamageNumbersWidgetClass));
	}

	if (DamageNumbers)
	{
		DamageNumbers->PlaceAtWorldLocation(Cast<APlayerController>(EventInstigator), Location);
		DamageNumbers->SetDamageNumber(Damage);
	}

	Health = FMath::Clamp(Health - Damage.Damage, 0.0f, MaxHealth);
	if (Health == 0.0f)
	{
		KillOwner();
	}
}






