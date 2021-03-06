// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/DamageType.h"
#include "../../Widgets/WorldPositionedWidget/DamageNumbersWidget.h"
#include "../../Interfaces/DamageableObjectInterface.h"

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

void UHealthComponent::NotifyDeath()
{
	if (GetOwner()->GetClass()->ImplementsInterface(UDamageableObjectInterface::StaticClass()))
	{
		IDamageableObjectInterface::Execute_NotifyDeath(GetOwner());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UHealthComponent of actor %s cannot notify the actor because it doesnt implement the IDamageableObjectInterface"), *GetOwner()->GetName());
	}
	//GetOwner()->K2_DestroyActor();
}

void UHealthComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (HealthRegenRate && Health <= MaxHealth)
	{
		Health = FMath::Clamp(Health + HealthRegenRate * DeltaTime, 0.0f, MaxHealth);
	}
}

void UHealthComponent::AddDamage(FDamageCompute Damage, AController* EventInstigator, AActor* DamageCauser, const FHitResult& Hit, bool bIsExplosion)
{
	ComputeDamageAfterDefence(Damage);
	ComputeDamageAfterResistance(Damage);
	ComputeDamageAfterStatus(Damage);

	FVector Location;
	if (!bIsExplosion && Hit.bBlockingHit)
	{
		Location = Hit.ImpactPoint;
	}
	else if (AActor* OwnerActor = GetOwner())
	{
		Location = OwnerActor->GetActorLocation();
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
		NotifyDeath();
	}
}

void UHealthComponent::HealByAmmount(float HealAmmount)
{
	Health = FMath::Clamp(Health + HealAmmount, 0.0f, MaxHealth);
}

