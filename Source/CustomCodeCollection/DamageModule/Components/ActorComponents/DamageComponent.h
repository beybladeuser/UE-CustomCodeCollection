// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "DamageComponent.generated.h"

class UDamageType;
class UDamageNumbersWidget;

USTRUCT(BlueprintType)
struct FDamageCompute
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 CritLvl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Resistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TSubclassOf<UDamageNumbersWidget> DamageNumbersWidgetClass;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CUSTOMCODECOLLECTION_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TSubclassOf<UDamageNumbersWidget> DamageNumbersWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage|Primitives")
	float Damage = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage|Primitives")
	TSubclassOf<UDamageType> DamageType;
	//0.0 == 0% ; 1.0 == 100%
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage|Crits", meta = (ClampMin = "0"))
	float CritChance = 0.5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage|Crits", meta = (ClampMin = "0"))
	float CritMultiplier = 2.0;

	//Defines the percentage of damage depending on the charge percentage of the ChargeGun(its recommended that you leave the time between 0 and 1, as this is the time percent)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage|Charge|Primitives")
	FRuntimeFloatCurve DamageChargeVariation;
	FKeyHandle DamageChargeVariationDefaultHandle1;
	FKeyHandle DamageChargeVariationDefaultHandle2;

	//Defines the percentage of damage depending on the charge percentage of the ChargeGun(its recommended that you leave the time between 0 and 1, as this is the time percent)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage|Charge|Crits")
	FRuntimeFloatCurve CritChanceChargeVariation;
	FKeyHandle CritChanceChargeVariationDefaultHandle1;
	FKeyHandle CritChanceChargeVariationDefaultHandle2;

	//Defines the percentage of damage depending on the charge percentage of the ChargeGun(its recommended that you leave the time between 0 and 1, as this is the time percent)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage|Charge|Crits")
	FRuntimeFloatCurve CritMultiplierChargeVariation;
	FKeyHandle CritMultiplierChargeVariationDefaultHandle1;
	FKeyHandle CritMultiplierChargeVariationDefaultHandle2;

	// Called when the game starts
	virtual void BeginPlay() override;

	bool IsCrit(float Charge);
	float GetCritDamage(float Charge, int32& OutCritLvl);

public:	
	UFUNCTION(BlueprintCallable)
	FDamageCompute ComputeFlatDamage(float Charge = 1.f);

	void DamageActor(float ChargePercentage, AActor* OtherActor, const FHitResult& Hit, bool IsExplosion);
};
