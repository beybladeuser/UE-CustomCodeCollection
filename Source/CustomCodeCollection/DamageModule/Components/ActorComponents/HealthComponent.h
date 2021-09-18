// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageComponent.h"
#include "HealthComponent.generated.h"

class UDamageType;
struct FDamageCompute;
class ADamageNumberBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CUSTOMCODECOLLECTION_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defences")
	float Health = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defences")
	float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defences")
	float Defence = 10.f;
	//Pair (damagetype, res in 0-1 scale)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defences", meta = (ClampMax="1"))
	TMap<TSubclassOf<UDamageType>, float> Resistences;

	//if HealthRegenRate > 0 health heals by HealthRegenRate each second; if HealthRegenRate < 0 health Drains by -HealthRegenRate each second; if HealthRegenRate == 0 nothing appens
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defences|Healing")
	float HealthRegenRate = 0.f;

	// Called when the game starts
	virtual void BeginPlay() override;

	float GetResistance(TSubclassOf<UDamageType> DamageType);
	// TODO - add Defence functionality
	void ComputeDamageAfterDefence(FDamageCompute& Damage);
	void ComputeDamageAfterResistance(FDamageCompute& Damage);
	// TODO - add status handling
	void ComputeDamageAfterStatus(FDamageCompute& Damage);
	void HandleStatus();

	//dont forget that you can override the K2_DestroyActor function(in c++ only :( ) of the Actor class for specific dying behaviour
	void NotifyDeath();

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddDamage(FDamageCompute Damage, AController* EventInstigator, AActor* DamageCauser, const FHitResult& Hit, bool bIsExplosion);

	UFUNCTION(BlueprintCallable)
	void HealByAmmount(float HealAmmount);
};
